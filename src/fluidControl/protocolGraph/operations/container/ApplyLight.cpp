/*
 * ApplyLight.cpp
 *
 *  Created on: 28 de mar. de 2016
 *      Author: angel
 */

#include "ApplyLight.h"

ApplyLight::ApplyLight() : ContainerOperation() {
	this->sourceId = -1;
	this->wavelength = boost::shared_ptr<MathematicOperable>();
	this->intensity = boost::shared_ptr<MathematicOperable>();
}

ApplyLight::ApplyLight(const ApplyLight& node) : ContainerOperation(node) {
	this->sourceId = node.sourceId;
	this->wavelength = node.wavelength;
	this->intensity = node.intensity;
}

std::string ApplyLight::toText() {
	return patch::to_string(containerID) + "[label=\"applyLigth("
			+ patch::to_string(sourceId) + ", " + wavelength.get()->toString()
			+ ", " + intensity.get()->toString() + ")\"];";
}

void ApplyLight::loadNode(const std::string& line) throw (std::invalid_argument) {
	//TODO: JSON
}

ApplyLight::ApplyLight(int idContainer,boost::shared_ptr<Mapping> mapping, int sourceID,
		boost::shared_ptr<MathematicOperable> wavelength,
		boost::shared_ptr<MathematicOperable> intensity) :
			ContainerOperation(idContainer, mapping){
	this->sourceId = sourceID;
	this->wavelength = wavelength;
	this->intensity = intensity;
}

ApplyLight::~ApplyLight() {

}

void ApplyLight::execute() {
	executable.get()->applyLight(sourceId, wavelength.get()->getValue(), intensity.get()->getValue());
}
