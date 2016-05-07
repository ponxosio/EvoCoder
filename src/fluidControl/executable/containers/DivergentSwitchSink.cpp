/*
 * DivergentSwitchSink.cpp
 *
 *  Created on: 4 de may. de 2016
 *      Author: angel
 */

#include "../../executable/containers/DivergentSwitchSink.h"

DivergentSwitchSink::DivergentSwitchSink() :
		ExecutableContainerNode() {
	this->insert = boost::shared_ptr<Injector>();
	this->extractor = boost::shared_ptr<Extractor>();
	this->control = boost::shared_ptr<Control>();
}

DivergentSwitchSink::DivergentSwitchSink(const DivergentSwitchSink& node) :
		ExecutableContainerNode(node) {
	this->insert = node.insert;
	this->extractor = node.extractor;
	this->control = node.control;
}

DivergentSwitchSink::DivergentSwitchSink(int idConatiner, float capacity,
		boost::shared_ptr<Injector> insert,
		boost::shared_ptr<Extractor> extractor,
		boost::shared_ptr<Control> control) :
		ExecutableContainerNode(idConatiner,
				boost::shared_ptr<ContainerNodeType>(new ContainerNodeType(
						ContainerNodeType::fromIntToMovementType(insert.get()->getMovementType()),
						ContainerType::divergent_switch_sink)), capacity) {

	this->insert = insert;
	this->extractor = extractor;
	this->control = control;
}

DivergentSwitchSink::~DivergentSwitchSink() {

}

std::string DivergentSwitchSink::toText() {
	//TODO: definir
}

void DivergentSwitchSink::loadNode(const std::string& line)
		throw (std::invalid_argument) {
	//TODO: JSON
}

void DivergentSwitchSink::receiveLiquid(int source, int target, double rate)
		throw (std::invalid_argument) {
	this->insert.get()->injectLiquid(rate);
}

void DivergentSwitchSink::extractLiquid(int source, int target, double rate)
		throw (std::invalid_argument) {
	this->control.get()->setConnection(source, target);
	this->extractor.get()->extractLiquid(rate);
}

void DivergentSwitchSink::connectContainer(int source, int target) {
	if (containerID == source) {
		this->control.get()->addConnection(source, target);
	}
}
