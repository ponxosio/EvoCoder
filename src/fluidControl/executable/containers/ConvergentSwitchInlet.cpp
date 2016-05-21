/*
 * ConvergentSwitchInlet.cpp
 *
 *  Created on: 4 de may. de 2016
 *      Author: angel
 */

#include "../../executable/containers/ConvergentSwitchInlet.h"

ConvergentSwitchInlet::ConvergentSwitchInlet() :
		ExecutableContainerNode() {
	this->insert = std::shared_ptr<Injector>();
	this->extractor = std::shared_ptr<Extractor>();
	this->control = std::shared_ptr<Control>();
}

ConvergentSwitchInlet::ConvergentSwitchInlet(const ConvergentSwitchInlet& node) :
		ExecutableContainerNode(node) {
	this->insert = node.insert;
	this->extractor = node.extractor;
	this->control = node.control;
}

ConvergentSwitchInlet::ConvergentSwitchInlet(int idConatiner, float capacity,
		std::shared_ptr<Injector> insert,
		std::shared_ptr<Extractor> extractor,
		std::shared_ptr<Control> control) :
		ExecutableContainerNode(idConatiner,
				std::shared_ptr<ContainerNodeType>(new ContainerNodeType(
						ContainerNodeType::fromIntToMovementType(extractor.get()->getMovementType()),
						ContainerType::convergent_switch_inlet)), capacity) {

	this->insert = insert;
	this->extractor = extractor;
	this->control = control;
}

ConvergentSwitchInlet::~ConvergentSwitchInlet() {

}

/*std::string ConvergentSwitchInlet::toText() {
	//TODO: definir
}*/

void ConvergentSwitchInlet::loadNode(const std::string& line)
		throw (std::invalid_argument) {
	//TODO: JSON
}

void ConvergentSwitchInlet::receiveLiquid(double rate)
		throw (std::invalid_argument) {
	this->insert.get()->injectLiquid(rate);
}

void ConvergentSwitchInlet::extractLiquid(double rate)
		throw (std::invalid_argument) {
	this->extractor.get()->extractLiquid(rate);
}

void ConvergentSwitchInlet::setPositionInject(int source, int target) {
	this->control.get()->setConnection(source, target);
}

void ConvergentSwitchInlet::setPositionExtract(int source, int target) {
}

void ConvergentSwitchInlet::connectContainer(int source, int target) {
	if (containerID == target) {
		this->control.get()->addConnection(source, target);
	}
}
