/*
 * InletContainer.cpp
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#include "../../executable/containers/InletContainer.h"

InletContainer::InletContainer() : ExecutableContainerNode() {
	this->ext = boost::shared_ptr<Extractor>();
}

InletContainer::InletContainer(const InletContainer& node) : ExecutableContainerNode(node) {
	this->ext = node.ext;
}

InletContainer::InletContainer(int idContainer, float capacity,
		boost::shared_ptr<Extractor> ext) : ExecutableContainerNode(idContainer, boost::shared_ptr<ContainerNodeType>(new ContainerNodeType(
				ContainerNodeType::fromIntToMovementType(ext.get()->getMovementType()),
				ContainerType::inlet)), capacity) {
	this->ext = ext;
}

InletContainer::~InletContainer() {}

std::string InletContainer::toText() {
	//TODO: por definir
}

void InletContainer::loadNode(const std::string& line)
		throw (std::invalid_argument) {
	//TODO:Json
}

void InletContainer::receiveLiquid(int source, int target, double rate) throw (std::invalid_argument) {
	throw(std::invalid_argument("this container cannot receive liquid"));
}

void InletContainer::extractLiquid(int source, int target, double rate) throw (std::invalid_argument) {
	ext.get()->extractLiquid(rate);
}

void InletContainer::connectContainer(int source, int target) {
}
