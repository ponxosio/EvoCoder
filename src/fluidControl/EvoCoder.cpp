/*
 * EvoCoder.cpp
 *
 *  Created on: 6 de mar. de 2016
 *      Author: angel
 */

#include "EvoCoder.h"

using namespace std;

EvoCoder::EvoCoder(ProtocolGraph* protocol,
		std::shared_ptr<VariableTable> table, std::shared_ptr<Mapping> mapping) {
	this->protocol = protocol;
	this->table = table;
	this->mapping = mapping;
	this->actual = NULL;
}

EvoCoder::~EvoCoder() {
	//delete mapping;
}

bool EvoCoder::exec_general() throw (std::invalid_argument) {
	bool correct = false;
	CommunicationsInterface::GetInstance()->setTesting(false);
	mapping->settesting(false);
	try {
		sketcher();
		mapping->doMapping();

		table.get()->clear();
		initilizeTime();

		mapping->setExec_general();
		mapping->startCommunications();
		correct = exec();
		mapping->stopCommunications();
	} catch (std::invalid_argument& e) {
		LOG(ERROR) << "exception while executing, " << e.what();
	} catch (std::ios_base::failure& e) {
		LOG(ERROR) << "exception while connecting, " << e.what();
	}
	return correct;
}

bool EvoCoder::exec_ep() throw (std::invalid_argument) {
	bool correct = false;
	CommunicationsInterface::GetInstance()->setTesting(false);
	mapping->settesting(false);
	try {
		sketcher();
		mapping->doMapping();

		table.get()->clear();
		initilizeTime();

		mapping->setExec_ep();
		mapping->startCommunications();
		correct = exec();
		mapping->stopCommunications();
	} catch (std::invalid_argument& e) {
		LOG(ERROR)<< "exception while executing, " << e.what();
	} catch (std::ios_base::failure& e) {
		LOG(ERROR) << "exception while connecting, " << e.what();
	}
	return correct;
}

bool EvoCoder::test() throw (std::invalid_argument) {
	bool correct = false;
	CommunicationsInterface::GetInstance()->setTesting(true);
	try {
		sketcher();
		mapping->doMapping();

		table.get()->clear();
		initilizeTime();

		mapping->setExec_general();
		mapping->settesting(true);
		mapping->startCommunications();
		correct = exec();
		mapping->stopCommunications();
	} catch (std::invalid_argument& e) {
		LOG(ERROR)<< "exception while executing, " << e.what();
	} catch (std::ios_base::failure& e) {
		LOG(ERROR) << "exception while connecting, " << e.what();
	}
	return correct;
}

bool EvoCoder::sketcher() {
	table.get()->clear();
	initilizeTime();
	mapping->setSketching();
	mapping->settesting(false);

	ProtocolGraph::ProtocolNodeVectorPtr operations = protocol->getAllNodes();
	for (auto it = operations->begin(); it != operations->end(); ++it) {
		ProtocolGraph::ProtocolNodePtr cast = *it;
		try {
			cast->execute();
		}
		catch (std::invalid_argument& e) {
			LOG(WARNING) << e.what();
		}
	}
	return true;
}

bool EvoCoder::exec() {
	bool vuelta = true;
	actual = protocol->getStart();

	if (actual != NULL) {
		ProtocolNodeQueue pending;
		pending.push(actual);

		while (!pending.empty()) {
			actual = pending.front();
			pending.pop();
			actual->execute();
			addAvailableEdges(pending);
		}
	} else {
		LOG(FATAL)<< "protocol does not has an starting node";
		vuelta = false;
	}
	return vuelta;
}

void EvoCoder::addAvailableEdges(ProtocolNodeQueue & nodes) {
	const ProtocolGraph::ProtocolEdgeVectorPtr neighbor = protocol->getProjectingEdges(
			actual->getContainerId());

	LOG(DEBUG) << "adding " << neighbor->size() << " neighbors...";
	for (auto it = neighbor->begin(); it != neighbor->end(); ++it) {
		ProtocolGraph::ProtocolEdgePtr cast = *it;
		if (cast->conditionMet()) {
			nodes.push(protocol->getNode(cast->getIdTarget()));
		}
	}
}

void EvoCoder::initilizeTime() {
	table->setValue(TIME_VARIABLE , 0.0);
	mapping->setTimestamp(Utils::getCurrentTimeMilis());
}
