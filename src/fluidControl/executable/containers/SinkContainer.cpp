/*
 * SinkContainer.cpp
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#include "../../executable/containers/SinkContainer.h"

SinkContainer::SinkContainer() :
		ExecutableContainerNode() {
	this->insert = boost::shared_ptr<Injector>();
}

SinkContainer::SinkContainer(const SinkContainer& node) :
		ExecutableContainerNode(node) {
	this->insert = node.insert;
}

SinkContainer::SinkContainer(int idContainer, float capacity,
		boost::shared_ptr<Injector> insert) :
		ExecutableContainerNode(idContainer, boost::shared_ptr<ContainerNodeType>(new ContainerNodeType(
				MovementType::irrelevant,
				ContainerType::sink)), capacity) {
	this->insert = insert;
}

SinkContainer::~SinkContainer() {
}

std::string SinkContainer::toText() {
	//TODO: definir
}

void SinkContainer::loadNode(const std::string& line)
		throw (std::invalid_argument) {
	//TODO: JSON
}

void SinkContainer::receiveLiquid(int source, int target, double rate)
		throw (std::invalid_argument) {
	insert.get()->injectLiquid(rate);
}

void SinkContainer::extractLiquid(int source, int target, double rate)
		throw (std::invalid_argument) {
	throw(std::invalid_argument("liquid cannot be extracted from this container "));
}

void SinkContainer::connectContainer(int source, int target) {
}
