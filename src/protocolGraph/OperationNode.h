/*
 * OperationNode.h
 *
 *  Created on: 23 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONNODE_H_
#define SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONNODE_H_

#include <string>

//local
#include "../graph/Node.h"

/**
 * Interface that implements a node that can be executed
 */
class OperationNode: public Node {
public:
	OperationNode() : Node() {}
	OperationNode(const OperationNode & obj) : Node(obj) {}
	OperationNode(int idContainer) : Node(idContainer){}
	virtual ~OperationNode(){}

	virtual void execute() = 0;
};

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONNODE_H_ */
