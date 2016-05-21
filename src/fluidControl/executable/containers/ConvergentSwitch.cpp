/*
 * ConvergentSwitch.cpp
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#include "../../executable/containers/ConvergentSwitch.h"

ConvergentSwitch::ConvergentSwitch() :
		ExecutableContainerNode() {
	this->insert = std::shared_ptr<Injector>();
	this->control = std::shared_ptr<Control>();
}

ConvergentSwitch::ConvergentSwitch(const ConvergentSwitch& node) {
	this->insert = node.insert;
	this->control = node.control;
}

ConvergentSwitch::ConvergentSwitch(int idConatiner, float capacity,
		std::shared_ptr<Injector> insert, std::shared_ptr<Control> control) :
		ExecutableContainerNode(idConatiner,
				std::shared_ptr<ContainerNodeType>(new ContainerNodeType(
						MovementType::irrelevant,
						ContainerType::convergent_switch)), capacity) {
	this->insert = insert;
	this->control = control;
}

ConvergentSwitch::~ConvergentSwitch() {

}

/*std::string ConvergentSwitch::toText() {
	//TODO definir
}*/

void ConvergentSwitch::loadNode(const std::string& line)
		throw (std::invalid_argument) {
	//TODO: JSON
}

void ConvergentSwitch::receiveLiquid(double rate)
		throw (std::invalid_argument) {
	insert.get()->injectLiquid(rate);
}

void ConvergentSwitch::extractLiquid(double rate)
		throw (std::invalid_argument) {
	throw(std::invalid_argument(
			"liquid cannot be extracted from this container "));
}

void ConvergentSwitch::setPositionInject(int source, int target) {
	control.get()->setConnection(source, target);
}

void ConvergentSwitch::setPositionExtract(int source, int target) {
}

void ConvergentSwitch::connectContainer(int source, int target) {
	if (containerID == target) {
		control.get()->addConnection(source, target);
	}
}
