/*
 * Transfer.cpp
 *
 *  Created on: 23 de mar. de 2016
 *      Author: angel
 */

#include "Transfer.h"

Transfer::Transfer() :
		ContainerOperation() {
	this->idSource = -1;
	this->idTarget = -1;
	this->volume = boost::shared_ptr<MathematicOperable>();
}

Transfer::Transfer(const Transfer& obj)  :
		ContainerOperation(obj) {

	this->idSource = obj.idSource;
	this->idTarget = obj.idTarget;
	this->volume = obj.volume;
}

Transfer::Transfer(int idContainer, boost::shared_ptr<Mapping> mapping,
		int idSource, int idTarget,
		boost::shared_ptr<MathematicOperable> volume) :
		ContainerOperation(idContainer, mapping) {

	this->idSource = idSource;
	this->idTarget = idTarget;
	this->volume = volume;
}

std::string Transfer::toText() {
	return patch::to_string(containerID) + "[label=\"Transfer("
			+ patch::to_string(idSource) + ", " + patch::to_string(idTarget)
			+ ", " + volume.get()->toString() + ")\"];";
}

void Transfer::loadNode(const std::string& line) throw (invalid_argument) {
	//TODO: JSON
}

Transfer::~Transfer() {
	// TODO Auto-generated destructor stub
}

void Transfer::execute() {
	this->executable.get()->transfer(idSource, idTarget, volume.get()->getValue());
}