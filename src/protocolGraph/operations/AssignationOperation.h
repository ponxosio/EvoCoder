/*
 * AsignationOperation.h
 *
 *  Created on: 23 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_ASSIGNATIONOPERATION_H_
#define SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_ASSIGNATIONOPERATION_H_

#include <string>

//boost
#include <boost/shared_ptr.hpp>

//local
#include "../../util/Utils.h"
#include "../../operables/mathematics/VariableEntry.h"
#include "../../operables/mathematics/MathematicOperable.h"
#include "../OperationNode.h"

/**
 * Implements a variable assignation, for example "t = 3 + d*2"
 */
class AssignationOperation: public OperationNode {
public:
	//methods of node
	AssignationOperation();
	AssignationOperation(const AssignationOperation & node);

	virtual string toText();
	virtual void loadNode(const string & line) throw (invalid_argument);
	//
	/**
	 *
	 * @param idContainer id of the node
	 * @param receiver variable whose value is going to be changed
	 * @param value numeric value to assign to the variable
	 */
	AssignationOperation(int idContainer,
			boost::shared_ptr<VariableEntry> receiver,
			boost::shared_ptr<MathematicOperable> value);

	virtual ~AssignationOperation();

	/**
	 * Executes the assignation
	 */
	virtual void execute();
protected:
	/**
	 * variable whose value is going to be changed
	 */
	boost::shared_ptr<VariableEntry> receiver;
	/**
	 * numeric value to assign to the variable
	 */
	boost::shared_ptr<MathematicOperable> value;
};

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_ASSIGNATIONOPERATION_H_ */
