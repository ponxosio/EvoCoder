/*
 * ControlNode.cpp
 *
 *  Created on: 23 de mar. de 2016
 *      Author: angel
 */

#include "LoopNode.h"

LoopNode::LoopNode() :
		OperationNode() {
	this->conditionIN = boost::shared_ptr<ComparisonOperable>();
	this->conditionOUT = boost::shared_ptr<ComparisonOperable>();
}

LoopNode::LoopNode(const LoopNode& obj) :
		OperationNode(obj) {
	this->conditionIN = obj.conditionIN;
	this->conditionOUT = obj.conditionOUT;
}

LoopNode::LoopNode(int containerId,
		boost::shared_ptr<ComparisonOperable> conditionIN,
		boost::shared_ptr<ComparisonOperable> conditionOUT) :
		OperationNode(containerId) {
	this->conditionIN = conditionIN;
	this->conditionOUT = conditionOUT;
}

LoopNode::~LoopNode() {

}

string LoopNode::toText() {
	return patch::to_string(containerID) + "[ label =\"" + LOOP_STRING + "("
			+ conditionIN.get()->toString() + ")\"];";
}

void LoopNode::loadNode(const string& line) throw (invalid_argument) {
	//TODO: cuando este definido como JSON
}

void LoopNode::execute() {
}