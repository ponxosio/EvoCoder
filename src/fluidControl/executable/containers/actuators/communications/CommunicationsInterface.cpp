/*
 * CommunicationsInterface.cpp
 *
 *  Created on: 15 de may. de 2016
 *      Author: angel
 */

#include "CommunicationsInterface.h"

CommunicationsInterface *CommunicationsInterface::m_pInstance = NULL;

void CommunicationsInterface::freeCommandInterface() {
	delete m_pInstance;
}

CommunicationsInterface::CommunicationsInterface() {
	this->communicationMap = new std::tr1::unordered_map<int, CommandSender*>();
	this->testCommunicationMap = new std::tr1::unordered_map<int, CommandSender*>();
	this->testing = false;
	this->lastId = 0;
	this->testLastId = 0;
}

CommunicationsInterface::~CommunicationsInterface() {
	for (auto it = communicationMap->begin(); it != communicationMap->end();
			++it) {
		CommandSender* actual = (*it).second;
		delete actual;
	}
	delete communicationMap;

	for (auto it = testCommunicationMap->begin();
			it != testCommunicationMap->end(); ++it) {
		CommandSender* actual = (*it).second;
		delete actual;
	}
	delete testCommunicationMap;
}

int CommunicationsInterface::addCommandSender(CommandSender* communications) {
	int nextId;
	if (!testing) {
		nextId = lastId;
		communicationMap->insert(std::make_pair(nextId, communications));
		lastId++;
	} else {
		nextId = testLastId;
		testCommunicationMap->insert(std::make_pair(nextId, communications));
		testLastId++;
	}
	return nextId;
}

CommandSender* CommunicationsInterface::getCommandSender(int communicationId) {
	typename std::tr1::unordered_map<int, CommandSender*>::iterator it;
	CommandSender* finded = NULL;

	if (!testing) {
		it = communicationMap->find(communicationId);
	} else {
		it = testCommunicationMap->find(communicationId);
	}

	if (it != communicationMap->end()) {
		finded = (*it).second;
	}
	return finded;
}
