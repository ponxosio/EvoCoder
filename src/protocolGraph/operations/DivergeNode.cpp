/*
 * DivergeNode.cpp
 *
 *  Created on: 11 de abr. de 2016
 *      Author: angel
 */

#include "DivergeNode.h"

DivergeNode::DivergeNode() :
		OperationNode() {
	this->conditionIN = boost::shared_ptr<ComparisonOperable>();
	this->conditionOUT = boost::shared_ptr<ComparisonOperable>();
	this->endNode = NULL;
}

DivergeNode::DivergeNode(const DivergeNode& node) :
		OperationNode(node) {
	this->conditionIN = node.conditionIN;
	this->conditionOUT = node.conditionOUT;
	this->endNode = node.endNode;
}

DivergeNode::DivergeNode(int containerId,
		boost::shared_ptr<ComparisonOperable> conditionIN,
		boost::shared_ptr<ComparisonOperable> conditionOUT) :
		OperationNode(containerId) {
	this->conditionIN = conditionIN;
	this->conditionOUT = conditionOUT;
	this->endNode = NULL;
}

DivergeNode::~DivergeNode() {}

string DivergeNode::toText() {
	return patch::to_string(containerID) + "[ label =\"" + DIVERGE_STRING + "("
			+ conditionIN.get()->toString() + ")\"];";
}

void DivergeNode::loadNode(const string& line) throw (invalid_argument) {
	//TODO: JSON
}

void DivergeNode::execute() {
	LOG(DEBUG) << "execute: " << conditionIN.get()->toString();
}
