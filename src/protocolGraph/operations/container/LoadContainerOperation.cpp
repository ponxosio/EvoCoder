/*
 * LoadContainer.cpp
 *
 *  Created on: 5 de abr. de 2016
 *      Author: angel
 */

#include "LoadContainerOperation.h"

LoadContainerOperation::LoadContainerOperation(): ContainerOperation() {
	this->value = boost::shared_ptr<MathematicOperable>();
	this->idSource = -1;
}

LoadContainerOperation::LoadContainerOperation(const LoadContainerOperation& obj) : ContainerOperation(obj) {
	this->value = obj.value;
	this->idSource = obj.idSource;
}

LoadContainerOperation::LoadContainerOperation(int idConatiner,
		boost::shared_ptr<Mapping> executable,
		int idSource,
		boost::shared_ptr<MathematicOperable> value) : ContainerOperation(idConatiner, executable) {

	this->value = value;
	this->idSource = idSource;
}

LoadContainerOperation::~LoadContainerOperation() {
}

std::string LoadContainerOperation::toText() {
	return patch::to_string(containerID) + "[label=\"loadContainer("
			+ patch::to_string(idSource) + ", " + value.get()->toString()
			+ ")\"];";
}

void LoadContainerOperation::loadNode(const std::string& line)
		throw (std::invalid_argument) {
	//TODO: JSON
}

void LoadContainerOperation::execute() {
	executable.get()->loadContainer(this->idSource, value.get()->getValue());
}
