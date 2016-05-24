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

	//TYPE DEFS
	typedef Graph<OperationNode, ConditionEdge>::NodeTypePtr ProtocolNodePtr;
	typedef Graph<OperationNode, ConditionEdge>::EdgeTypePtr ProtocolEdgePtr;

	typedef Graph<OperationNode, ConditionEdge>::NodeVector ProtocolNodeVector;
	typedef Graph<OperationNode, ConditionEdge>::EdgeVector ProtocolEdgeVector;

	typedef Graph<OperationNode, ConditionEdge>::NodeVectorPtr ProtocolNodeVectorPtr;
	typedef Graph<OperationNode, ConditionEdge>::EdgeVectorPtr ProtocolEdgeVectorPtr;
	//

	ProtocolGraph(const std::string & name);
	virtual ~ProtocolGraph();

	bool addOperation(ProtocolNodePtr node);
	bool connectOperation(ProtocolEdgePtr edge);
	bool connectOperation(ProtocolNodePtr nodeSource, ProtocolNodePtr nodeTarget, std::shared_ptr<ComparisonOperable> comparison);

	ProtocolNodePtr getStart();
	void setStartNode(int idStart);

	inline typename ProtocolNodePtr getNode(int idNode) {
		return graph->getNode(idNode);
	}
	inline const ProtocolEdgeVectorPtr getProjectingEdges(int idNode) {
		return graph->getLeavingEdges(idNode);
	}
	inline typename ProtocolNodeVectorPtr getAllNodes() {
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

	ProtocolEdgePtr makeEdge(int idSource, int idTarget, std::shared_ptr<ComparisonOperable> comparison);

};

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_PROTOCOLGRAPH_H_ */
