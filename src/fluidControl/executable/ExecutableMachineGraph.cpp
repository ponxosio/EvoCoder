/*
 * ExecutableMachineGraph.cpp
 *
 *  Created on: 9 de mar. de 2016
 *      Author: angel
 */

#include "../executable/ExecutableMachineGraph.h"

//static
void ExecutableMachineGraph::toJSON(const std::string & path, const ExecutableMachineGraph & machine) {
	ofstream o(path);
	LOG(DEBUG) << "serializating ExecutableMachineGraph to " + path;
	cereal::JSONOutputArchive ar(o);
	ar(machine);
}
ExecutableMachineGraph* ExecutableMachineGraph::fromJSON(const std::string & path) {
	ifstream i(path);
	LOG(DEBUG) << "loading ExecutableMachine from " + path;
	cereal::JSONInputArchive arIn(i);
	
	ExecutableMachineGraph machine;
	arIn(machine);
	return new ExecutableMachineGraph(machine);
}
//


ExecutableMachineGraph::ExecutableMachineGraph() {
	this->name = "undefined";
	this->graph = std::make_shared<Graph<ExecutableContainerNode, Edge>>();
	this->usedNodes = std::make_shared<std::unordered_set<int>>();
	this->usedEges = std::make_shared<std::unordered_set<std::tuple<int, int>, PairIntIntHashFunction>>();
}

ExecutableMachineGraph::ExecutableMachineGraph(const ExecutableMachineGraph & exMachine) {
	this->name = exMachine.name;
	this->graph = exMachine.graph;
	this->usedNodes = exMachine.usedNodes;
	this->usedEges = exMachine.usedEges;
}

ExecutableMachineGraph::ExecutableMachineGraph(const std::string & name) {
	this->name = name;
	this->graph = std::make_shared<Graph<ExecutableContainerNode, Edge>>();
	this->usedNodes = std::make_shared<std::unordered_set<int>>();
	this->usedEges = std::make_shared<std::unordered_set<std::tuple<int, int>, PairIntIntHashFunction>>();
}

ExecutableMachineGraph::~ExecutableMachineGraph() {
	//delete graph;
	//delete usedNodes;
	//delete usedEges;
}

void ExecutableMachineGraph::addContainer(ExecutableContainerNodePtr node) {
	this->graph->addNode(node);
}

typename ExecutableMachineGraph::ExecutableContainerNodePtr ExecutableMachineGraph::getContainer(int idConatiner) {
	return this->graph->getNode(idConatiner);
}

bool ExecutableMachineGraph::connectExecutableContainer(int idSource,
	int idTarget) {
	bool vuelta = false;
	if (existsContainer(idSource) && existsContainer(idTarget)
		&& !areConected(idSource, idTarget)) {
		ExecutableMachineGraph::ExecutableContainerEdgePtr newEdge = makeEdge(idSource, idTarget);
		graph->addEdge(newEdge);

		Graph<ExecutableContainerNode, Edge>::NodeTypePtr source = graph->getNode(idSource);
		Graph<ExecutableContainerNode, Edge>::NodeTypePtr target = graph->getNode(idTarget);
		source->connectContainer(idSource, idTarget);
		target->connectContainer(idSource, idTarget);

		vuelta = true;
	}
	return vuelta;
}

void ExecutableMachineGraph::printMachine(const std::string& path) {
	graph->saveGraph(path);
}

ExecutableMachineGraph::FlowHeap ExecutableMachineGraph::getAvailableFlows(
	const ContainerNodeType& tipoIni, const ContainerNodeType& tipofin, const ExecutableContainerNodeVector & subgraph) {

	FlowHeap flows;
	ExecutableContainerNodeVector available = getAllCompatibleNodes(tipoIni, subgraph);

	for (auto it = available.begin(); it != available.end(); ++it) {
		vector<int> visitados;
		ExecutableContainerEdgeVector recorridos;
		ExecutableContainerNodePtr actual = *it;
		getAvailableFlows_recursive_type(actual->getContainerId(), visitados, recorridos, flows, actual, tipofin, false);
	}
	return flows;
}

ExecutableMachineGraph::FlowHeap ExecutableMachineGraph::getAvailableFlows(int idConatinerInit, const ContainerNodeType& tipofin) {

	FlowHeap flows;

	vector<int> visitados;
	ExecutableContainerEdgeVector recorridos;
	ExecutableContainerNodePtr actual = graph->getNode(idConatinerInit);
	getAvailableFlows_recursive_type(idConatinerInit, visitados, recorridos, flows,	actual, tipofin, false);
	return flows;
}

ExecutableMachineGraph::FlowHeap ExecutableMachineGraph::getAvailableFlows(const ContainerNodeType& tipoIni, int idContainerFin) {

	FlowHeap flows;

	vector<int> visitados;
	ExecutableContainerEdgeVector recorridos;
	ExecutableContainerNodePtr actual = graph->getNode(idContainerFin);
	getAvailableFlows_recursive_type(idContainerFin, visitados, recorridos, flows,
		actual, tipoIni, true);

	return flows;
}

ExecutableMachineGraph::FlowHeap ExecutableMachineGraph::getAvailableFlows(int idInit, int idFin) {

	FlowHeap flows;

	vector<int> visitados;
	ExecutableContainerEdgeVector recorridos;
	ExecutableContainerNodePtr actual = graph->getNode(idInit);
	getAvailableFlows_recursive_id(idInit, visitados, recorridos,
		flows, actual, idFin);

	return flows;
}

void ExecutableMachineGraph::addUsedEdge(int idSorce, int idTarget) {
	usedEges->insert(std::tuple<int, int>(idSorce, idTarget));
}

void ExecutableMachineGraph::removeUsedEdge(int idSorce, int idTarget) {
	usedEges->erase(std::tuple<int, int>(idSorce, idTarget));
}

bool ExecutableMachineGraph::isEdgeAvailable(ExecutableContainerEdgePtr edge) {
	return (usedEges->find(
		std::tuple<int, int>(edge->getIdSource(), edge->getIdTarget()))
		== usedEges->end());
}

bool ExecutableMachineGraph::isEdgeAvailable(int idSource, int idTarget) {
	return (usedEges->find(
		std::tuple<int, int>(idSource, idTarget))
		== usedEges->end());
}

ExecutableMachineGraph::ExecutableContainerEdgeVector ExecutableMachineGraph::getAvailableEdges(
	ExecutableContainerNodePtr actual, bool reversed) {

	ExecutableContainerEdgeVector available;
	ExecutableContainerEdgeVectorPtr edges;
	if (reversed) {
		edges = graph->getArrivingEdges(actual->getContainerId());
	}
	else {
		edges = graph->getLeavingEdges(actual->getContainerId());
	}

	for (auto it = edges->begin(); it != edges->end(); ++it) {
		ExecutableContainerEdgePtr actualE = *it;
		if (isEdgeAvailable(actualE)) {
			available.push_back(actualE);
		}
	}
	return available;
}

void ExecutableMachineGraph::getAvailableFlows_recursive_type(int idSource, vector<int> & visitados, ExecutableContainerEdgeVector & recorridos,
	FlowHeap & flows,
	ExecutableContainerNodePtr actual, const ContainerNodeType & destinationType, bool reversed) {

	visitados.push_back(actual->getContainerId());
	ExecutableContainerEdgeVector neighbors = getAvailableEdges(actual, reversed);
	for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
		ExecutableContainerEdgePtr actualNeig = *it;
		int id;
		if (reversed) {
			id = actualNeig->getIdSource();
		}
		else {
			id = actualNeig->getIdTarget();
		}
		if (isNodeAvailable(id)
			&& find(visitados.begin(), visitados.end(),
				id) == visitados.end()) {
			recorridos.push_back(actualNeig);
			ExecutableContainerNodePtr nodeTarget = graph->getNode(id);
			if (nodeTarget->getType()->isCompatible(destinationType)) {
				if (reversed) {
					flows.push(Flow<Edge>(id, idSource, recorridos));
				}
				else {
					flows.push(Flow<Edge>(idSource, id, recorridos));
				}
			}
			getAvailableFlows_recursive_type(idSource, visitados, recorridos, flows, nodeTarget, destinationType, reversed);
			recorridos.pop_back();
		}
	}
}

void ExecutableMachineGraph::getAvailableFlows_recursive_id(int idSource,
	vector<int>& visitados, ExecutableContainerEdgeVector & recorridos,
	FlowHeap & flows,
	ExecutableContainerNodePtr actual, int idDestination) {

	visitados.push_back(actual->getContainerId());
	ExecutableContainerEdgeVector neighbors = getAvailableEdges(actual, false);
	for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
		ExecutableContainerEdgePtr actualNeig = *it;
		int id = actualNeig->getIdTarget();

		if (id == idDestination) {
			recorridos.push_back(actualNeig);
			flows.push(Flow<Edge>(idSource, id, recorridos));
			recorridos.pop_back();
		}
		else if (isNodeAvailable(id)
			&& find(visitados.begin(), visitados.end(), id)
			== visitados.end()) {

			recorridos.push_back(actualNeig);
			ExecutableContainerNodePtr nodeTarget = graph->getNode(id);
			getAvailableFlows_recursive_id(idSource, visitados, recorridos,
				flows, nodeTarget, idDestination);
			recorridos.pop_back();
		}
	}
}

ExecutableMachineGraph::ExecutableContainerNodeVector ExecutableMachineGraph::getAllCompatibleNodes(
	const ContainerNodeType& type, const ExecutableContainerNodeVector & subgraph) {
	ExecutableContainerNodeVector available;

	for (auto it = subgraph.begin(); it != subgraph.end(); ++it) {
		ExecutableContainerNodePtr actual = *it;
		if (isNodeAvailable(actual) && actual->getType()->isCompatible(type)) {
			available.push_back(actual);
		}
	}
	return available;
}

bool ExecutableMachineGraph::isNodeAvailable(ExecutableContainerNodePtr node) {
	return (usedNodes->find(node->getContainerId()) == usedNodes->end());
}

bool ExecutableMachineGraph::isNodeAvailable(int nodeId) {
	return (usedNodes->find(nodeId) == usedNodes->end());
}

void ExecutableMachineGraph::addUsedNode(int nodeId) {
	usedNodes->insert(nodeId);
}

void ExecutableMachineGraph::removeUsedNode(int nodeId) {
	usedNodes->erase(nodeId);
}

ExecutableMachineGraph::ExecutableContainerEdgePtr ExecutableMachineGraph::makeEdge(int idSource, int idTarget) {
	return std::make_shared<Edge>(idSource, idTarget);
}

float ExecutableMachineGraph::getVolume(int idContainer) {
	return graph->getNode(idContainer)->getVolume();
}

void ExecutableMachineGraph::addVolume(int idContainer, float volume) {
	ExecutableContainerNodePtr actual = graph->getNode(idContainer);
	if (actual != NULL) {
		double newVolume = actual->getVolume() + volume;
		if (newVolume <= actual->getCapacity()) {
			actual->setVolume(newVolume);
			LOG(DEBUG) << "idContainer " << idContainer << " new volume = " << newVolume << "ml";
		}
		else {
			LOG(WARNING) << "volume of container " + patch::to_string(idContainer) + " is over capacity";
		}
	}
}

void ExecutableMachineGraph::substractVolume(int idContainer, float volume) {
	ExecutableContainerNodePtr actual = graph->getNode(idContainer);
	if (actual != NULL) {
		double newVolume = actual->getVolume() - volume;
		if (newVolume >= 0) {
			actual->setVolume(newVolume);
			LOG(DEBUG) << "idContainer " << idContainer << " new volume = " << newVolume << "ml";
		}
		else {
			LOG(WARNING) << "volume of container " + patch::to_string(idContainer) + " is less than 0";
		}
	}
}