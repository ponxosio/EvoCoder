/*
 * ExecutableMachineGraph.cpp
 *
 *  Created on: 9 de mar. de 2016
 *      Author: angel
 */

#include "../executable/ExecutableMachineGraph.h"

ExecutableMachineGraph::ExecutableMachineGraph(const std::string & name) {
	this->name = name;
	this->graph = new Graph<ExecutableContainerNode, Edge>();
	this->usedNodes = new std::tr1::unordered_set<int>();
	this->usedEges = new std::tr1::unordered_set<std::pair<int,int>,PairIntIntHashFunction>();
}

ExecutableMachineGraph::~ExecutableMachineGraph() {
	delete graph;
	delete usedNodes;
	delete usedEges;
}

void ExecutableMachineGraph::addContainer(ExecutableContainerNode* node) {
	this->graph->addNode(node);
}

ExecutableContainerNode* ExecutableMachineGraph::getContainer(int idConatiner) {
	return this->graph->getNode(idConatiner);
}

bool ExecutableMachineGraph::connectExecutableContainer(int idSource,
		int idTarget) {
	bool vuelta = false;
	if (existsContainer(idSource) && existsContainer(idTarget)
			&& !areConected(idSource, idTarget)) {
		Edge* newEdge = new Edge(idSource, idTarget);
		graph->addEdge(newEdge);

		ExecutableContainerNode* source = graph->getNode(idSource);
		ExecutableContainerNode* target = graph->getNode(idTarget);
		source->connectContainer(idSource, idTarget);
		target->connectContainer(idSource, idTarget);

		vuelta = true;
	}
	return vuelta;
}

void ExecutableMachineGraph::printMachine(const std::string& path) {
	graph->saveGraph(path);
}

std::priority_queue<Flow<Edge> , vector<Flow<Edge>>,
		FlowPtrComparator<Edge> >  ExecutableMachineGraph::getAvailableFlows(
		const ContainerNodeType& tipoIni, const ContainerNodeType& tipofin, const std::vector<ExecutableContainerNode*> & subgraph) {

	std::priority_queue<Flow<Edge> , vector<Flow<Edge>>,
			FlowPtrComparator<Edge>> flows;
	vector<ExecutableContainerNode*> available = getAllCompatibleNodes(tipoIni, subgraph);

	for (auto it = available.begin(); it != available.end(); ++it) {
		vector<int> visitados;
		vector<Edge*> recorridos;
		ExecutableContainerNode* actual = *it;
		getAvailableFlows_recursive_type(actual->getContainerId(), visitados, recorridos, flows, actual, tipofin, false);
	}
	return flows;
}

std::priority_queue<Flow<Edge> , vector<Flow<Edge> >, FlowPtrComparator<Edge> > ExecutableMachineGraph::getAvailableFlows(
		int idConatinerInit, const ContainerNodeType& tipofin) {

	std::priority_queue<Flow<Edge> , vector<Flow<Edge> >,
				FlowPtrComparator<Edge>> flows;

	vector<int> visitados;
	vector<Edge*> recorridos;
	ExecutableContainerNode* actual = graph->getNode(idConatinerInit);
	getAvailableFlows_recursive_type(idConatinerInit, visitados, recorridos, flows,
			actual, tipofin, false);
	return flows;
}

std::priority_queue<Flow<Edge>, vector<Flow<Edge> >, FlowPtrComparator<Edge> > ExecutableMachineGraph::getAvailableFlows(
		const ContainerNodeType& tipoIni, int idContainerFin) {

	std::priority_queue<Flow<Edge>, vector<Flow<Edge> >, FlowPtrComparator<Edge>> flows;

	vector<int> visitados;
	vector<Edge*> recorridos;
	ExecutableContainerNode* actual = graph->getNode(idContainerFin);
	getAvailableFlows_recursive_type(idContainerFin, visitados, recorridos, flows,
			actual, tipoIni, true);

	return flows;
}

std::priority_queue<Flow<Edge>, vector<Flow<Edge> >, FlowPtrComparator<Edge> > ExecutableMachineGraph::getAvailableFlows(
		int idInit, int idFin) {

	std::priority_queue<Flow<Edge>, vector<Flow<Edge> >, FlowPtrComparator<Edge>> flows;

	vector<int> visitados;
	vector<Edge*> recorridos;
	ExecutableContainerNode* actual = graph->getNode(idInit);
	getAvailableFlows_recursive_id(idInit, visitados, recorridos,
			flows, actual, idFin);

	return flows;
}

void ExecutableMachineGraph::addUsedEdge(int idSorce, int idTarget) {
	usedEges->insert(std::pair<int,int>(idSorce, idTarget));
}

void ExecutableMachineGraph::removeUsedEdge(int idSorce, int idTarget) {
	usedEges->erase(std::pair<int,int>(idSorce, idTarget));
}

bool ExecutableMachineGraph::isEdgeAvailable(Edge* edge) {
	return (usedEges->find(
			std::pair<int, int>(edge->getIdSource(), edge->getIdTarget()))
			== usedEges->end());
}

bool ExecutableMachineGraph::isEdgeAvailable(int idSource, int idTarget) {
	return (usedEges->find(
				std::pair<int, int>(idSource, idTarget))
				== usedEges->end());
}

vector<Edge*> ExecutableMachineGraph::getAvailableEdges(
		ExecutableContainerNode* actual, bool reversed) {
	vector<Edge*> available;
	const vector<Edge*>* edges;
	if (reversed) {
		edges = graph->getArrivingEdges(actual->getContainerId());
	} else {
		edges = graph->getLeavingEdges(actual->getContainerId());
	}

	for (auto it = edges->begin(); it != edges->end(); ++it) {
		Edge* actual = *it;
		if (isEdgeAvailable(actual)) {
			available.push_back(actual);
		}
	}
	return available;
}

void ExecutableMachineGraph::getAvailableFlows_recursive_type(int idSource, vector<int> & visitados, vector<Edge*> & recorridos,
		std::priority_queue<Flow<Edge>, vector<Flow<Edge>>,
				FlowPtrComparator<Edge> >& flows,
		ExecutableContainerNode* actual, const ContainerNodeType & destinationType, bool reversed) {

	visitados.push_back(actual->getContainerId());
	vector<Edge*> neighbors = getAvailableEdges(actual, reversed);
	for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
		Edge* actualNeig = *it;
		int id;
		if (reversed) {
			id = actualNeig->getIdSource();
		} else {
			id = actualNeig->getIdTarget();
		}
		if (isNodeAvailable(id)
				&& find(visitados.begin(), visitados.end(),
						id) == visitados.end()) {
			recorridos.push_back(actualNeig);
			ExecutableContainerNode* nodeTarget = graph->getNode(id);
			if (nodeTarget->getType()->isCompatible(destinationType)) {
				if (reversed) {
					flows.push(Flow<Edge>(id, idSource, recorridos));
				} else {
					flows.push(Flow<Edge>(idSource, id, recorridos));
				}
			}
			getAvailableFlows_recursive_type(idSource, visitados, recorridos, flows, nodeTarget, destinationType, reversed);
			recorridos.pop_back();
		}
	}
}

void ExecutableMachineGraph::getAvailableFlows_recursive_id(int idSource,
		vector<int>& visitados, vector<Edge*>& recorridos,
		std::priority_queue<Flow<Edge>, vector<Flow<Edge> >,
				FlowPtrComparator<Edge> >& flows,
		ExecutableContainerNode* actual, int idDestination) {

	visitados.push_back(actual->getContainerId());
	vector<Edge*> neighbors = getAvailableEdges(actual, false);
	for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
		Edge* actualNeig = *it;
		int id = actualNeig->getIdTarget();

		if (id == idDestination) {
			recorridos.push_back(actualNeig);
			flows.push(Flow<Edge>(idSource, id, recorridos));
			recorridos.pop_back();
		} else if (isNodeAvailable(id)
				&& find(visitados.begin(), visitados.end(), id)
						== visitados.end()) {

			recorridos.push_back(actualNeig);
			ExecutableContainerNode* nodeTarget = graph->getNode(id);
			getAvailableFlows_recursive_id(idSource, visitados, recorridos,
					flows, nodeTarget, idDestination);
			recorridos.pop_back();
		}
	}
}

vector<ExecutableContainerNode*> ExecutableMachineGraph::getAllCompatibleNodes(
	const ContainerNodeType& type, const std::vector<ExecutableContainerNode*> & subgraph) {
	vector<ExecutableContainerNode*> available;

	for (auto it = subgraph.begin(); it != subgraph.end(); ++it) {
		ExecutableContainerNode* actual = *it;
		if (isNodeAvailable(actual) && actual->getType()->isCompatible(type)) {
			available.push_back(actual);
		}
	}
	return available;
}

bool ExecutableMachineGraph::isNodeAvailable(ExecutableContainerNode* node) {
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
