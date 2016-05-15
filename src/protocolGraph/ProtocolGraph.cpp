/*
 * ProtocolGraph.cpp
 *
 *  Created on: 9 de mar. de 2016
 *      Author: angel
 */

#include "ProtocolGraph.h"

ProtocolGraph::ProtocolGraph(const std::string & name) {
	this->name = name;
	this->idStart = -1;
	this->graph = new Graph<OperationNode, ConditionEdge>();
}

ProtocolGraph::~ProtocolGraph() {
	delete graph;
}

bool ProtocolGraph::addOperation(OperationNode* node) {
	return graph->addNode(node);
}

bool ProtocolGraph::connectOperation(ConditionEdge* edge) {
	return graph->addEdge(edge);
}

OperationNode* ProtocolGraph::getStart() {
	return graph->getNode(idStart);
}

void ProtocolGraph::setStartNode(int idStart) {
	this->idStart = idStart;
}

bool ProtocolGraph::connectOperation(OperationNode* nodeSource,
		OperationNode* nodeTarget,
		boost::shared_ptr<ComparisonOperable> comparison) {

	ConditionEdge* edge = new ConditionEdge(nodeSource->getContainerId(), nodeTarget->getContainerId(), comparison);
	return connectOperation(edge);
}
