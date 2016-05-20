/*
 * DivergeNode.h
 *
 *  Created on: 11 de abr. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_DIVERGENODE_H_
#define SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_DIVERGENODE_H_

//types strings
#define DIVERGE_STRING "if"

#include <string>

//boost
#include <boost/shared_ptr.hpp>

//local
#include "../../util/Utils.h"
#include "../../operables/comparison/ComparisonOperable.h"
#include "../OperationNode.h"

class DivergeNode: public OperationNode {
public:
	//Methods for Node
	DivergeNode();
	DivergeNode(const DivergeNode & node);

	virtual string toText();
	virtual void loadNode(const string & line) throw (invalid_argument);
	//
	DivergeNode(int containerId,
			boost::shared_ptr<ComparisonOperable> conditionIN,
			boost::shared_ptr<ComparisonOperable> conditionOUT);
	virtual ~DivergeNode();

	virtual void execute();

	//GETTERS & SETTERS
	const boost::shared_ptr<ComparisonOperable>& getConditionIN() const {
		return conditionIN;
	}
	const boost::shared_ptr<ComparisonOperable>& getConditionOUT() const {
		return conditionOUT;
	}
	OperationNode* getEndNode() const {
		return endNode;
	}
	void setEndNode(OperationNode* endNode) {
		this->endNode = endNode;
	}

protected:
	boost::shared_ptr<ComparisonOperable> conditionIN;
	boost::shared_ptr<ComparisonOperable> conditionOUT;
	OperationNode* endNode;
};

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_DIVERGENODE_H_ */
