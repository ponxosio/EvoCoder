/*
 * ApplyTemperature.cpp
 *
 *  Created on: 28 de mar. de 2016
 *      Author: angel
 */

#include "ApplyTemperature.h"

ApplyTemperature::ApplyTemperature() : ContainerOperation() {
	this->sourceId = -1;
	this->degress = std::shared_ptr<MathematicOperable>();
}

ApplyTemperature::ApplyTemperature(const ApplyTemperature& node) : ContainerOperation(node) {
	this->sourceId = node.sourceId;
	this->degress = node.degress;
}

std::string ApplyTemperature::toText() {
	return patch::to_string(containerID) + "[label=\"applyTemperature("
			+ patch::to_string(sourceId) + ", " + degress.get()->toString()
			+ ")\"];";
}

void ApplyTemperature::loadNode(const std::string& line)
		throw (std::invalid_argument) {
	//TODO: JSON
}

ApplyTemperature::ApplyTemperature(int containerId,
		std::shared_ptr<Mapping> mapping, int sourceId,
		std::shared_ptr<MathematicOperable> degress) :
		ContainerOperation(containerId, mapping) {

	this->sourceId = sourceId;
	this->degress = degress;
}

ApplyTemperature::~ApplyTemperature() {}

void ApplyTemperature::execute() {
	executable.get()->applyTemperature(sourceId, degress.get()->getValue());
}
