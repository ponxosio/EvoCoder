/*
 * FlowContainer.cpp
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#include "../../executable/containers/FlowContainer.h"

FlowContainer::FlowContainer() : ExecutableContainerNode() {
	this->extract = boost::shared_ptr<Extractor>();
	this->insert = boost::shared_ptr<Injector>();
}

FlowContainer::FlowContainer(const FlowContainer& node) : ExecutableContainerNode(node) {
	this->extract = node.extract;
	this->insert = node.insert;
}

FlowContainer::FlowContainer(int idContainer, float capacity,
		boost::shared_ptr<Extractor> extract, boost::shared_ptr<Injector> insert) :
		ExecutableContainerNode(idContainer, boost::shared_ptr<ContainerNodeType>(new ContainerNodeType(
				ContainerNodeType::fromIntToMovementType(extract.get()->getMovementType()),
				ContainerType::flow)),
				capacity) {

	this->extract = extract;
	this->insert = insert;
}

FlowContainer::~FlowContainer() {
	// TODO Auto-generated destructor stub
}

/*std::string FlowContainer::toText() {
	//TODO: DEFINIR
}*/

void FlowContainer::loadNode(const std::string& line)
		throw (std::invalid_argument) {
	//TODO:JSON
}

void FlowContainer::receiveLiquid(int source, int target, double rate)
		throw (std::invalid_argument) {
	this->insert.get()->injectLiquid(rate);
}

void FlowContainer::extractLiquid(int source, int target, double rate)
		throw (std::invalid_argument) {
	this->extract.get()->extractLiquid(rate);
}

void FlowContainer::connectContainer(int source, int target) {
}
