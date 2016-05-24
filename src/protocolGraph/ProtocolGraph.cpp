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

bool ProtocolGraph::addOperation(ProtocolNodePtr node) {
	return graph->addNode(node);
}

bool ProtocolGraph::connectOperation(ProtocolEdgePtr edge) {
	return graph->addEdge(edge);
}

ProtocolGraph::ProtocolNodePtr ProtocolGraph::getStart() {
	return graph->getNode(idStart);
}

void ProtocolGraph::setStartNode(int idStart) {
	this->idStart = idStart;
}

bool ProtocolGraph::connectOperation(ProtocolNodePtr nodeSource,
		ProtocolNodePtr nodeTarget,
		std::shared_ptr<ComparisonOperable> comparison) {

	ProtocolEdgePtr edge = makeEdge(nodeSource->getContainerId(), nodeTarget->getContainerId(), comparison);
	return connectOperation(edge);
}

ProtocolGraph::ProtocolEdgePtr ProtocolGraph::makeEdge(int idSource, int idTarget, std::shared_ptr<ComparisonOperable> comparison) {
	//return new ConditionEdge(idSource, idTarget, comparison);
	return std::make_shared<ConditionEdge>(idSource, idTarget, comparison);
}
