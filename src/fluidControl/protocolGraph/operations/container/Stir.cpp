/*
 * Stir.cpp
 *
 *  Created on: 4 de may. de 2016
 *      Author: angel
 */

#include "Stir.h"

Stir::Stir() : ContainerOperation() {
	this->sourceId = -1;
	this->intensity = boost::shared_ptr<MathematicOperable>();
}

Stir::Stir(const Stir& node) :
		ContainerOperation(node) {
	this->sourceId = node.sourceId;
	this->intensity = node.intensity;
}

Stir::Stir(int containerId, boost::shared_ptr<Mapping> executable, int sourceId,
		boost::shared_ptr<MathematicOperable> intensity) :
		ContainerOperation(containerId, executable) {
	this->sourceId = sourceId;
	this->intensity = intensity;
}

Stir::~Stir() {}

std::string Stir::toText() {
	return patch::to_string(containerID) + "[label=\"applyTemperature("
			+ patch::to_string(sourceId) + ", " + intensity.get()->toString()
			+ ")\"];";
}

void Stir::loadNode(const std::string& line) throw (std::invalid_argument) {
	//TODO: JSON
}

void Stir::execute() {
	this->executable.get()->stir(sourceId, intensity.get()->getValue());
}
