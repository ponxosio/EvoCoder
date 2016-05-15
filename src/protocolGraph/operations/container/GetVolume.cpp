/*
 * GetVolume.cpp
 *
 *  Created on: 28 de mar. de 2016
 *      Author: angel
 */

#include "GetVolume.h"

GetVolume::GetVolume() : ContainerOperation() {
	this->sourceId = -1;
	this->receiver = boost::shared_ptr<VariableEntry>();
}

GetVolume::GetVolume(const GetVolume& node) : ContainerOperation(node){
	this->sourceId = node.sourceId;
	this->receiver = node.receiver;
}

GetVolume::GetVolume(int containerId, boost::shared_ptr<Mapping> mapping,
		int sourceId, boost::shared_ptr<VariableEntry> receiver) :
		ContainerOperation(containerId, mapping) {
	this->sourceId = sourceId;
	this->receiver = receiver;
}

GetVolume::~GetVolume() {}

std::string GetVolume::toText() {
	return patch::to_string(containerID) + "[label=\""
			+ receiver.get()->toString() + " = getVolume("
			+ patch::to_string(sourceId) + ")\"];";
}

void GetVolume::loadNode(const std::string& line) throw (invalid_argument) {
	//TODO: JSON
}

void GetVolume::execute() {
	receiver.get()->setValue(executable.get()->getVolume(sourceId));
}