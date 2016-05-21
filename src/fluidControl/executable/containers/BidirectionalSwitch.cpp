/*
 * BidirectionalSwitch.cpp
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#include "../../executable/containers/BidirectionalSwitch.h"

BidirectionalSwitch::BidirectionalSwitch() : ExecutableContainerNode() {
	this->extract = boost::shared_ptr<Extractor>();
	this->insert = boost::shared_ptr<Injector>();
	this->controlIN = boost::shared_ptr<Control>();
	this->controlOUT = boost::shared_ptr<Control>();
}

BidirectionalSwitch::BidirectionalSwitch(const BidirectionalSwitch& node) : ExecutableContainerNode(node) {
	this->extract =  node.extract;
	this->insert =  node.insert;
	this->controlIN = node.controlIN;
	this->controlOUT = node.controlOUT;
}

BidirectionalSwitch::BidirectionalSwitch(int idContainer, float capacity,
		boost::shared_ptr<Extractor> extract,
		boost::shared_ptr<Injector> insert,
		boost::shared_ptr<Control> controlIN,
		boost::shared_ptr<Control> controlOUT) :
		ExecutableContainerNode(idContainer, boost::shared_ptr<ContainerNodeType>(new ContainerNodeType(
				ContainerNodeType::fromIntToMovementType(extract.get()->getMovementType()),
				ContainerType::bidirectional_switch)), capacity) {

	this->extract = extract;
	this->insert = insert;
	this->controlIN = controlIN;
	this->controlOUT = controlOUT;
}

BidirectionalSwitch::~BidirectionalSwitch() {

}

/*std::string BidirectionalSwitch::toText() {
	//TODO: DEFINIR
}*/

void BidirectionalSwitch::loadNode(const std::string& line)
		throw (std::invalid_argument) {
	//TODO: JSON
}

void BidirectionalSwitch::receiveLiquid(double rate)
		throw (std::invalid_argument) {
	insert.get()->injectLiquid(rate);
}

void BidirectionalSwitch::extractLiquid(double rate)
		throw (std::invalid_argument) {
	extract.get()->extractLiquid(rate);
}

void BidirectionalSwitch::setPositionExtract(int source, int target) {
	controlOUT.get()->setConnection(source, target);
}

void BidirectionalSwitch::setPositionInject(int source, int target) {
	controlIN.get()->setConnection(source, target);
}

void BidirectionalSwitch::connectContainer(int source, int target) {
	if (containerID == source) {
		controlOUT.get()->addConnection(source, target);
	} else if (containerID == target) {
		controlIN.get()->addConnection(source, target);
	}
}
