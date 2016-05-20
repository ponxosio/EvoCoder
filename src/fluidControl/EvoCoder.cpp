/*
 * EvoCoder.cpp
 *
 *  Created on: 6 de mar. de 2016
 *      Author: angel
 */

#include "EvoCoder.h"

using namespace std;

EvoCoder::EvoCoder(ProtocolGraph* protocol,
		boost::shared_ptr<VariableTable> table, Mapping* mapping) {
	this->protocol = protocol;
	this->table = table;
	this->mapping = mapping;
	this->actual = NULL;
}

EvoCoder::~EvoCoder() {
	delete mapping;
}

bool EvoCoder::exec_general() {
	table.get()->clear();
	initilizeTime();
	mapping->setExec_general();

	return exec();
}

bool EvoCoder::exec_ep() {
	table.get()->clear();
	initilizeTime();
	mapping->setExec_ep();

	return exec();
}

bool EvoCoder::test() {
	table.get()->clear();
	initilizeTime();
	mapping->setTest();

	return execRelaxed();
}

bool EvoCoder::sketcher() {
	table.get()->clear();
	initilizeTime();
	mapping->setSketching();

	vector<OperationNode*> operations = protocol->getAllNodes();
	for (auto it = operations.begin(); it != operations.end(); ++it) {
		OperationNode* cast = *it;
		cast->execute();
	}
	return true;
}

bool EvoCoder::exec() {
	bool vuelta = true;
	actual = protocol->getStart();

	if (actual != NULL) {
		queue<OperationNode*> pending;
		pending.push(actual);

		while (!pending.empty()) {
			actual = pending.front();
			pending.pop();
			actual->execute();
			addAvailableEdges(&pending);
		}
	} else {
		LOG(FATAL)<< "protocol does not has an starting node";
		vuelta = false;
	}
	return vuelta;
}

bool EvoCoder::execRelaxed() {
	bool vuelta = true;
	actual = protocol->getStart();

	if (actual != NULL) {
		LOG(DEBUG) << "executing execRelaxed for " << protocol->getName() << "...";

		vector<LoopNode*> loopsBeingExecuted;
		queue<OperationNode*> pending;
		vector<std::pair<DivergeNode*,bool>> branchChosen;
		pending.push(actual);

		while (!pending.empty()) {
			execRelaxed_ProcessNode(&loopsBeingExecuted, &pending, &branchChosen);
		}
	} else {
		LOG(FATAL)<< "protocol does not has an starting node";
		vuelta = false;
	}
	return vuelta;
}

void EvoCoder::execRelaxed_newBranch(OperationNode* start,
		std::vector<LoopNode*> loopsBeingExecuted,
		std::queue<OperationNode*> pending,
		std::vector<std::pair<DivergeNode*,bool>> branchChosen) {

	actual = start;
	pending.push(start);
	while (!pending.empty()) {
		execRelaxed_ProcessNode(&loopsBeingExecuted, &pending, &branchChosen);
	}

}

void EvoCoder::execRelaxed_ProcessNode(
		std::vector<LoopNode*>* loopsBeingExecuted,
		std::queue<OperationNode*>* pending,
		std::vector<std::pair<DivergeNode*,bool>>* branchChosen) {

	LOG(DEBUG)<< "pending nodes: " << pending->size();
	actual = pending->front();
	pending->pop();
	LOG(DEBUG) << "executing node " << actual->toText() << "...";

	actual->execute();
	/*
	 * if is a control Node, loop or if, must be checked if the condition is physical
	 */
	if (Utils::IsType<LoopNode, OperationNode>(actual)) {
		LoopNode* cast = dynamic_cast<LoopNode*>(actual);
		if (cast->getConditionIN().get()->isPhysical()
				|| cast->getConditionOUT().get()->isPhysical()) {

			execRelaxed_ProcessLoopNode(cast, loopsBeingExecuted, pending);
		} else { //if the condition is not physical we process it normally
			addAvailableEdges(pending);
		}
	} else if (Utils::IsType<DivergeNode, OperationNode>(actual)) {
		DivergeNode* cast = dynamic_cast<DivergeNode*>(actual);
		if (cast->getConditionIN().get()->isPhysical()
				|| cast->getConditionOUT().get()->isPhysical()) {

			execRelaxed_ProcessDivergeNode(cast, loopsBeingExecuted, pending, branchChosen);
		} else { //if the condition is not physical we process it normally
			addAvailableEdges(pending);
		}
	} else { //if is not an if or loop, we process it normally
		addAvailableEdges(pending);
	}
}

void EvoCoder::execRelaxed_ProcessLoopNode(LoopNode* node,
		vector<LoopNode*>* loopsBeingExecuted, queue<OperationNode*>* nodes) {

	/*
	 * If we are in a loop , the first time arriving to the loop,
	 * we must enter through , the second we must exit.
	 */
	auto loopIterator = find(loopsBeingExecuted->begin(), loopsBeingExecuted->end(), node);
	if (loopIterator != loopsBeingExecuted->end()) { //checking if we have passed through this loop jet
		loopsBeingExecuted->erase(loopIterator);
		const vector<ConditionEdge*>* neighbor = protocol->getProjectingEdges(
				node->getContainerId());
		boost::shared_ptr<ComparisonOperable> conditionOUT =
				node->getConditionOUT();

		for (auto it = neighbor->begin(); it != neighbor->end(); ++it) {
			ConditionEdge* cast = *it;
			if (cast->hasCondition(conditionOUT.get())) {
				nodes->push(protocol->getNode(cast->getIdTarget()));
				//TODO: log enter out loop
			}
		}
	} else {
		const vector<ConditionEdge*>* neighbor = protocol->getProjectingEdges(
				node->getContainerId());
		boost::shared_ptr<ComparisonOperable> conditionIN =
				node->getConditionIN();

		for (auto it = neighbor->begin(); it != neighbor->end(); ++it) {
			ConditionEdge* cast = *it;
			if (cast->hasCondition(conditionIN.get())) {
				nodes->push(protocol->getNode(cast->getIdTarget()));
				//TODO: log enter in loop
			}
		}
	}
}

void EvoCoder::execRelaxed_ProcessDivergeNode(DivergeNode* node,
		std::vector<LoopNode*>* loopsBeingExecuted,
		std::queue<OperationNode*>* pending,
		std::vector<std::pair<DivergeNode*,bool>>* branchChosen) {

	if (!isLast(branchChosen, node)) {
		std::pair<DivergeNode*,bool> branch;
		const vector<ConditionEdge*>* neighbor = protocol->getProjectingEdges(
						node->getContainerId());
		if (isPresent(branchChosen, node, branch)) {
			boost::shared_ptr<ComparisonOperable> comparison;
			if (branch.second) {
				comparison = node->getConditionIN();
			} else {
				comparison = node->getConditionOUT();
			}
			for (auto it = neighbor->begin(); it != neighbor->end(); ++it) {
				ConditionEdge* cast = *it;
				if (cast->hasCondition(comparison.get())) {
					pending->push(protocol->getNode(cast->getIdTarget()));
				}
			}
		} else {
			boost::shared_ptr<ComparisonOperable> conditionIN = node->getConditionIN();
			boost::shared_ptr<ComparisonOperable> conditionOut = node->getConditionOUT();

			for (auto it = neighbor->begin(); it != neighbor->end(); ++it) {
				ConditionEdge* cast = *it;
				if (cast->hasCondition(conditionIN.get())) {
					branchChosen->push_back(make_pair(node, true));
					pending->push(protocol->getNode(cast->getIdTarget()));
				} else if (cast->hasCondition(conditionOut.get())) {
					branchChosen->push_back(make_pair(node, false));
					execRelaxed_newBranch(
							protocol->getNode(cast->getIdTarget()), *loopsBeingExecuted,
							*pending, *branchChosen);
				}
			}
		}
	}

}

void EvoCoder::addAvailableEdges(queue<OperationNode*>* nodes) {
	const vector<ConditionEdge*>* neighbor = protocol->getProjectingEdges(
			actual->getContainerId());

	LOG(DEBUG) << "adding " << neighbor->size() << " neighbors...";
	for (auto it = neighbor->begin(); it != neighbor->end(); ++it) {
		ConditionEdge* cast = *it;
		if (cast->conditionMet()) {
			nodes->push(protocol->getNode(cast->getIdTarget()));
		}
	}
}

bool EvoCoder::isLast(
		std::vector<std::pair<DivergeNode*, bool>>* branchChosen,
		DivergeNode* node) {

	std::pair<DivergeNode*, bool> last = branchChosen->back();
	return last.first->equals(*node);
}

bool EvoCoder::isPresent(
		std::vector<std::pair<DivergeNode*, bool>>* branchChosen,
		DivergeNode* node,
		std::pair<DivergeNode*, bool> & returned) {

	bool finded = false;
	for (auto it = branchChosen->begin();
			(it != branchChosen->end()) && !finded; ++it) {
		std::pair<DivergeNode*, bool> cast = *it;
		if (cast.first->equals(*node)) {
			finded = true;
			returned = cast;
		}
	}
	return finded;
}


void EvoCoder::initilizeTime() {
	table->setValue(TIME_VARIABLE , 0.0);
}

bool EvoCoder::doMapping() {
}
