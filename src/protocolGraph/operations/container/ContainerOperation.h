/*
 * ContainerOperation.h
 *
 *  Created on: 23 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONATINER_CONTAINEROPERATION_H_
#define SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONATINER_CONTAINEROPERATION_H_

#include <string>

//boost
#include <memory>

//local
#include "../../../util/Utils.h"
#include "../../../operables/mathematics/MathematicOperable.h"
#include "../../OperationNode.h"
#include "../../../fluidControl/Mapping.h"

/**
 * Interface that represents all the operations that can be made over the machine containers
 */
class ContainerOperation: public OperationNode {
public:
	ContainerOperation() : OperationNode() {
		this->executable = std::shared_ptr<Mapping>();
	}
	ContainerOperation(const ContainerOperation & obj) :
			OperationNode(obj) {
		this->executable = obj.executable;
	}
	ContainerOperation(int idConatiner, std::shared_ptr<Mapping> executable) : OperationNode(idConatiner) {
		this->executable = executable;
	}

	virtual ~ContainerOperation(){}

	virtual void execute() = 0;
protected:
	/**
	 * mapping where the operation can be executed
	 */
	std::shared_ptr<Mapping> executable;
};

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONATINER_CONTAINEROPERATION_H_ */
