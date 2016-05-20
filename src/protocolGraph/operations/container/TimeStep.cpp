/*
 * TimeStep.cpp
 *
 *  Created on: 28 de mar. de 2016
 *      Author: angel
 */

#include "TimeStep.h"

TimeStep::TimeStep() :
		ContainerOperation() {
	this->receiver = boost::shared_ptr<VariableEntry>();
}

TimeStep::TimeStep(const TimeStep& node) :
		ContainerOperation(node) {
	this->receiver = node.receiver;
}

TimeStep::TimeStep(int containerId, boost::shared_ptr<Mapping> mapping, boost::shared_ptr<VariableEntry> receiver) :
		ContainerOperation(containerId, mapping) {
	this->receiver = receiver;
}

TimeStep::~TimeStep() {
}

std::string TimeStep::toText() {
	return patch::to_string(containerID) + "[label=\"TimeStep()\"];";
}

void TimeStep::loadNode(const std::string& line) throw (invalid_argument) {
	//TODO: JSON
}

void TimeStep::execute() {
	receiver.get()->setValue(
			receiver.get()->getValue() + executable.get()->timeStept());
	LOG(DEBUG) << "time variable: " << receiver.get()->getValue();
}
