/*
 * ProtocolGraph.h
 *
 *  Created on: 9 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_PROTOCOLGRAPH_PROTOCOLGRAPH_H_
#define SRC_FLUIDCONTROL_PROTOCOLGRAPH_PROTOCOLGRAPH_H_

#include <string>

//data structures
#include <vector>

//boost
#include <memory>

//lib
#include "../../lib/easylogging++.h"

//local
#include "../graph/Graph.h"
#include "../operables/VariableTable.h"
#include "ConditionEdge.h"
#include "OperationNode.h"

class ProtocolGraph {
public:
	ProtocolGraph(const std::string & name);
	virtual ~ProtocolGraph();

	bool addOperation(OperationNode* node);
	bool connectOperation(ConditionEdge* edge);
	bool connectOperation(OperationNode* nodeSource, OperationNode* nodeTarget, std::shared_ptr<ComparisonOperable> comparison);

	std::shared_ptr<OperationNode> getStart();
	void setStartNode(int idStart);

	inline std::shared_ptr<OperationNode> getNode(int idNode) {
		return graph->getNode(idNode);
	}
	inline const std::vector<std::shared_ptr<ConditionEdge>> & getProjectingEdges(int idNode) {
		return graph->getLeavingEdges(idNode);
	}
	inline const std::vector<std::shared_ptr<OperationNode>> & getAllNodes() {
		return graph->getAllNodes();
	}

	inline void printProtocol(const std::string & path) {
		graph->saveGraph(path);
	}

	inline const std::string& getName() const {
		return name;
	}
protected:
	int idStart;
	std::string name;
	Graph<OperationNode, ConditionEdge>* graph;

};

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_PROTOCOLGRAPH_H_ */
