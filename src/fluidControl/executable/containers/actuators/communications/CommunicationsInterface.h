/*
 * CommunicationsInterface.h
 *
 *  Created on: 15 de may. de 2016
 *      Author: angel
 */

#ifndef FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_COMMUNICATIONS_COMMUNICATIONSINTERFACE_H_
#define FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_COMMUNICATIONS_COMMUNICATIONSINTERFACE_H_

#include <tr1/unordered_map>

#include "CommandSender.h"

class CommunicationsInterface {
public:
	static CommunicationsInterface* GetInstance() {
		if (!m_pInstance)
			m_pInstance = new CommunicationsInterface();
		return m_pInstance;
	}

	static void freeCommandInterface();

	int addCommandSender(CommandSender* communications);
	CommandSender* getCommandSender(int communicationId);

	inline void setTesting(bool testing) {
		m_pInstance->testing = testing;
	}

	~CommunicationsInterface();
private:
	CommunicationsInterface();
	CommunicationsInterface(const CommunicationsInterface& com){}
	CommunicationsInterface& operator=(const CommunicationsInterface&){}

	static CommunicationsInterface *m_pInstance;

	std::tr1::unordered_map<int, CommandSender*>* communicationMap;
	std::tr1::unordered_map<int, CommandSender*>* testCommunicationMap;
	bool testing;
	int lastId;
	int testLastId;
};

#endif /* FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_COMMUNICATIONS_COMMUNICATIONSINTERFACE_H_ */
