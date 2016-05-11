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
	this->usedNodes = new vector<ExecutableContainerNode*>();
}

ExecutableMachineGraph::~ExecutableMachineGraph() {
	delete graph;
	delete usedNodes;
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

std::priority_queue<Flow<Edge> *, vector<Flow<Edge> *>,
		FlowPtrComparator<Edge> >*  ExecutableMachineGraph::getAvailableFlows(
		const ContainerNodeType& tipoIni, const ContainerNodeType& tipofin) {

	std::priority_queue<Flow<Edge> *, vector<Flow<Edge> *>,
			FlowPtrComparator<Edge>>* flows = new std::priority_queue<
			Flow<Edge> *, vector<Flow<Edge> *>, FlowPtrComparator<Edge>>();
	vector<ExecutableContainerNode*> available = getAllCompatibleNodes(tipoIni);

	for (auto it = available.begin(); it != available.end(); ++it) {
		vector<int> visitados;
		vector<Edge*> recorridos;
		ExecutableContainerNode* actual = *it;
		getAvailableFlows_recursive(actual->getContainerId(), visitados, recorridos, flows, actual, tipofin);
	}
	return flows;
}

void ExecutableMachineGraph::getAvailableFlows_recursive(int idSource, vector<int> & visitados, vector<Edge*> & recorridos,
		std::priority_queue<Flow<Edge> *, vector<Flow<Edge> *>,
				FlowPtrComparator<Edge> >* flows,
		ExecutableContainerNode* actual, const ContainerNodeType & destinationType) {

	visitados.push_back(actual->getContainerId());
	const vector<Edge*>* neighbors = graph->getNeighbors(actual->getContainerId());
	for (auto it = neighbors->begin(); it != neighbors->end(); ++it) {
		Edge* actualNeig = *it;
		if (isNodeAvailable(actualNeig->getIdTarget())
				&& find(visitados.begin(), visitados.end(),
						actualNeig->getIdTarget()) == visitados.end()) {
			recorridos.push_back(actualNeig);
			ExecutableContainerNode* nodeTarget = graph->getNode(actualNeig->getIdTarget());
			if (nodeTarget->getType()->isCompatible(destinationType)) {
				Flow<Edge>* nFlow = new Flow<Edge>(idSource, actualNeig->getIdTarget(), recorridos);
				flows->push(nFlow);
			}
			getAvailableFlows_recursive(idSource, visitados, recorridos, flows, nodeTarget, destinationType);
			recorridos.pop_back();
		}
	}
}

bool ExecutableMachineGraph::isNodeInVector(ExecutableContainerNode* node, const vector<int>& nodesIds) {
	bool finded = false;
	auto it = nodesIds.begin();
	while(!finded && it != nodesIds.end()) {
		int actual = *it;
		finded  = (node->getContainerId() == actual);
		++it;
	}
	return finded;
}

vector<ExecutableContainerNode*> ExecutableMachineGraph::getAllCompatibleNodes(
	const ContainerNodeType& type) {
	vector<ExecutableContainerNode*> available;
	vector<ExecutableContainerNode*> nodos = graph->getAllNodes();

	for (auto it = nodos.begin(); it != nodos.end(); ++it) {
		ExecutableContainerNode* actual = *it;
		if (isNodeAvailable(actual) && actual->getType()->isCompatible(type)) {
			available.push_back(actual);
		}
	}
	return available;
}

bool ExecutableMachineGraph::isNodeAvailable(ExecutableContainerNode* node) {
	bool available = true;
	for (auto it = usedNodes->begin(); available && it != usedNodes->end(); ++it) {
		ExecutableContainerNode* actual = *it;
		available = !actual->equals(*node);
	}
	return available;
}

bool ExecutableMachineGraph::isNodeAvailable(int nodeId) {
	bool available = true;
	for (auto it = usedNodes->begin(); available && it != usedNodes->end();
			++it) {
		ExecutableContainerNode* actual = *it;
		available = actual->getContainerId() != nodeId;
	}
	return available;
}

void ExecutableMachineGraph::addUsedNode(int nodeId)
		throw (std::invalid_argument) {
	{
		ExecutableContainerNode* node = graph->getNode(nodeId);
		if (node != NULL) {
			usedNodes->push_back(node);
		} else {
			throw(std::invalid_argument("unknown nodeId: " + patch::to_string(nodeId)));
		}
	}
}
