/*
 * DivergentSwitch.cpp
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#include "DivergentSwitch.h"

DivergentSwitch::DivergentSwitch() :
		ExecutableContainerNode() {
	this->extract = boost::shared_ptr<Extractor>();
	this->control = boost::shared_ptr<Control>();
}

DivergentSwitch::DivergentSwitch(const DivergentSwitch& node) :
		ExecutableContainerNode(node) {
	this->extract = node.extract;
	this->control = node.control;
}

DivergentSwitch::DivergentSwitch(int idConatiner, float capacity,
		boost::shared_ptr<Extractor> extract,
		boost::shared_ptr<Control> control) :
		ExecutableContainerNode(idConatiner, boost::shared_ptr<ContainerNodeType>(new ContainerNodeType(
				ContainerNodeType::fromIntToMovementType(extract.get()->getMovementType()),
				ContainerType::divergent_switch)),
				capacity) {
	this->extract = extract;
	this->control = control;
}

DivergentSwitch::~DivergentSwitch() {

}

std::string DivergentSwitch::toText() {
	//TODO: definir
}

void DivergentSwitch::loadNode(const std::string& line)
		throw (std::invalid_argument) {
	//TODO: JSON
}

void DivergentSwitch::receiveLiquid(int source, int target, double rate)
		throw (std::invalid_argument) {
	throw(std::invalid_argument("this container cannot receive liquid"));
}

void DivergentSwitch::extractLiquid(int source, int target, double rate)
		throw (std::invalid_argument) {
	control.get()->setConnection(source, target);
	extract.get()->extractLiquid(rate);
}

void DivergentSwitch::connectContainer(int source, int target) {
	if (containerID == source) {
		control.get()->addConnection(source, target);
	}
}
