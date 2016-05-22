/*
 * MeasureOD.cpp
 *
 *  Created on: 28 de mar. de 2016
 *      Author: angel
 */

#include "MeasureOD.h"

MeasureOD::MeasureOD() : ContainerOperation(){
	this->sourceId = -1;
	this->receiver = std::shared_ptr<VariableEntry>();
}

MeasureOD::MeasureOD(const MeasureOD& node) : ContainerOperation(node) {
	this->sourceId = node.sourceId;
	this->receiver = node.receiver;
}

MeasureOD::MeasureOD(int containerId, std::shared_ptr<Mapping> mapping,
		int sourceId, std::shared_ptr<VariableEntry> receiver) :
		ContainerOperation(containerId, mapping) {
	this->sourceId = sourceId;
	this->receiver = receiver;
}

MeasureOD::~MeasureOD() {}

void MeasureOD::execute() {
	receiver.get()->setValue(executable.get()->measureOD(sourceId));
	receiver.get()->setPhysical(true);
}

std::string MeasureOD::toText() {
	return patch::to_string(containerID) + "[label=\""
			+ receiver.get()->toString() + " = measureOD("
			+ patch::to_string(sourceId) + ")\"];";
}

void MeasureOD::loadNode(const std::string& line) throw (invalid_argument) {
	//TODO: JSON
}
