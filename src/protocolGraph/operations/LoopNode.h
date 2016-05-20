/*
 * ControlNode.h
 *
 *  Created on: 23 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_LOOPNODE_H_
#define SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_LOOPNODE_H_

//types strings
#define LOOP_STRING "loop"

#include <string>

//boost
#include <boost/shared_ptr.hpp>

//lib
#include "../../../lib/easylogging++.h"

//local
#include "../../util/Utils.h"
#include "../../operables/comparison/ComparisonOperable.h"
#include "../OperationNode.h"

/**
 * Implements a flow control operation, if or while
 */
class LoopNode: public OperationNode {
public:
	//Methods for Node
	LoopNode();
	LoopNode(const LoopNode & node);

	virtual string toText();
	virtual void loadNode(const string & line) throw (invalid_argument);
	//
	LoopNode(int containerId, boost::shared_ptr<ComparisonOperable> conditionIN,
			boost::shared_ptr<ComparisonOperable> conditionOUT);

	virtual ~LoopNode();

	virtual void execute();

	//GETTERS & SETTERS
	const boost::shared_ptr<ComparisonOperable>& getConditionIN() const {
		return conditionIN;
	}
	const boost::shared_ptr<ComparisonOperable>& getConditionOUT() const {
		return conditionOUT;
	}

protected:
	boost::shared_ptr<ComparisonOperable> conditionIN;
	boost::shared_ptr<ComparisonOperable> conditionOUT;
};

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_LOOPNODE_H_ */
