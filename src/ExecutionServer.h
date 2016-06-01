#pragma once

#include <string>
#include <stdexcept>
#include <memory>
#include <unordered_map>

//lib
#include <easylogging++.h>

//local
#include "ExecutionMachineServer.h"
#include "fluidControl\EvoCoder.h"
#include "fluidControl\executable\ExecutableMachineGraph.h"
#include "fluidControl\executable\containers\actuators\communications\CommunicationsInterface.h"
#include "fluidControl\executable\containers\actuators\communications\CommandSender.h"
#include "operables\VariableTable.h"
#include "protocolGraph\ProtocolGraph.h"
#include "util\AutoEnumerate.h"
#include "util\Patch.h"
#include "util\Utils.h"

class ExecutionServer
{
public:
	static ExecutionServer* GetInstance() {
		if (!m_pInstance)
			m_pInstance = new ExecutionServer();
		return m_pInstance;
	}
	static void freeCommandInterface();

	~ExecutionServer();

	std::string executeProtocolOnNewMachine(const std::string & protocolJson, const std::string & machineJson);
	std::string executeProtocolOnExistingMachine(const std::string & protocolJson, const std::string & machineReference) throw (std::invalid_argument);

	std::shared_ptr<EvoCoder> getEvoCoder(const std::string & reference) throw (std::invalid_argument);
	std::string getMachineReference(const std::string& reference) throw (std::invalid_argument);

private:
	static ExecutionServer *m_pInstance;

	AutoEnumerate series;
	std::unordered_map<std::string, std::tuple<std::string, std::shared_ptr<EvoCoder>>> executionMap;

	ExecutionServer();
	ExecutionServer(const CommunicationsInterface& com) {}
	ExecutionServer& operator=(const CommunicationsInterface&) {}
};

