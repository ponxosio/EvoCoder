/*
 * SetContinousFlow.cpp
 *
 *  Created on: 23 de mar. de 2016
 *      Author: angel
 */

#include "../container/SetContinousFlow.h"

SetContinousFlow::SetContinousFlow() :
		ContainerOperation() {
	this->idSource = -1;
	this->idTarget = -1;
	this->rate = boost::shared_ptr<MathematicOperable>();
}

SetContinousFlow::SetContinousFlow(const SetContinousFlow& obj) :
		ContainerOperation(obj) {
	this->idSource = obj.idSource;
	this->idTarget = obj.idTarget;
	this->rate = obj.rate;
}

SetContinousFlow::SetContinousFlow(int idContainer,
		boost::shared_ptr<Mapping> mapping, int idSource, int idTarget,
		boost::shared_ptr<MathematicOperable> rate) :
		ContainerOperation(idContainer, mapping) {

	this->idSource = idSource;
	this->idTarget = idTarget;
	this->rate = rate;
}

SetContinousFlow::~SetContinousFlow() {
}

std::string SetContinousFlow::toText() {
	return patch::to_string(containerID) + "[label=\"setContinousFlow("
			+ patch::to_string(idSource) + ", " + patch::to_string(idTarget)
			+ ", " + rate.get()->toString() + ")\"];";
}

void SetContinousFlow::loadNode(const std::string& line)
		throw (invalid_argument) {
	//TODO: cuando se decida la sintaxis JSON
}

void SetContinousFlow::execute() {
	executable.get()->setContinuosFlow(idSource, idTarget, rate.get()->getValue());
}
