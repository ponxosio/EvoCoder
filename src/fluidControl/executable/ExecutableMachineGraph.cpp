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
}

ExecutableMachineGraph::~ExecutableMachineGraph() {
	delete graph;
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
