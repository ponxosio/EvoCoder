/*
 * ConvergentSwitchInlet.cpp
 *
 *  Created on: 4 de may. de 2016
 *      Author: angel
 */

#include "../../executable/containers/ConvergentSwitchInlet.h"

ConvergentSwitchInlet::ConvergentSwitchInlet() :
		ExecutableContainerNode() {
	this->insert = boost::shared_ptr<Injector>();
	this->extractor = boost::shared_ptr<Extractor>();
	this->control = boost::shared_ptr<Control>();
}

ConvergentSwitchInlet::ConvergentSwitchInlet(const ConvergentSwitchInlet& node) :
		ExecutableContainerNode(node) {
	this->insert = node.insert;
	this->extractor = node.extractor;
	this->control = node.control;
}

ConvergentSwitchInlet::ConvergentSwitchInlet(int idConatiner, float capacity,
		boost::shared_ptr<Injector> insert,
		boost::shared_ptr<Extractor> extractor,
		boost::shared_ptr<Control> control) :
		ExecutableContainerNode(idConatiner,
				boost::shared_ptr<ContainerNodeType>(new ContainerNodeType(
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

void ConvergentSwitchInlet::receiveLiquid(int source, int target, double rate)
		throw (std::invalid_argument) {
	this->control.get()->setConnection(source, target);
	this->insert.get()->injectLiquid(target);
}

void ConvergentSwitchInlet::extractLiquid(int source, int target, double rate)
		throw (std::invalid_argument) {
	this->extractor.get()->extractLiquid(rate);
}

void ConvergentSwitchInlet::connectContainer(int source, int target) {
	if (containerID == target) {
		this->control.get()->addConnection(source, target);
	}
}
