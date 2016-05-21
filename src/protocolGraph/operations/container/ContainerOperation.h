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

//cereal
#include <cereal/cereal.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>

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

	//SERIALIZATIoN
	template<class Archive>
	void serialize(Archive & ar, std::uint32_t const version);
protected:
	/**
	 * mapping where the operation can be executed
	 */
	std::shared_ptr<Mapping> executable;
};

template<class Archive>
inline void ContainerOperation::serialize(Archive& ar,
		const std::uint32_t version) {
	if (version <= 1) {
		OperationNode::serialize(ar, version);
		//ar(CEREAL_NVP(executable));
	}
}
// Associate some type with a version number
CEREAL_CLASS_VERSION( ContainerOperation, 1 );

// Include any archives you plan on using with your type before you register it
// Note that this could be done in any other location so long as it was prior
// to this file being included
#include <cereal/archives/json.hpp>
// Register DerivedClass
CEREAL_REGISTER_TYPE_WITH_NAME(ContainerOperation,"ContainerOperation");

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONATINER_CONTAINEROPERATION_H_ */
