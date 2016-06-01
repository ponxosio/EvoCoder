#include "ExecutionServer.h"

ExecutionServer* ExecutionServer::m_pInstance = NULL;

using namespace std;

void ExecutionServer::freeCommandInterface()
{
	delete m_pInstance;
}

ExecutionServer::ExecutionServer()
{
}

ExecutionServer::~ExecutionServer()
{
}

std::string ExecutionServer::executeProtocolOnNewMachine(const std::string & protocolJson, const std::string & machineJson)
{
	ExecutionMachineServer* machineServer = ExecutionMachineServer::GetInstance();
	string machineReference = machineServer->addNewMachine(machineJson);
	
	vector<int> coms;
	shared_ptr<ExecutableMachineGraph> machine = machineServer->getMachine(machineReference);
	coms.push_back(machineServer->getMachineComId(machineReference));

	shared_ptr<ProtocolGraph> protocol(ProtocolGraph::fromJSON(protocolJson));
	shared_ptr<VariableTable> table = make_shared<VariableTable>();
	
	string executionReference = "execution" + patch::to_string(series.getNextValue());
	protocol->updateReference(executionReference);

	shared_ptr<Mapping> map = make_shared<Mapping>(machine, protocol->getName() + "_" + machine->getName(), coms);
	shared_ptr<EvoCoder> evocoder = make_shared<EvoCoder>(protocol, table, map);

	executionMap.insert(make_pair(executionReference, tuple<string,shared_ptr<EvoCoder>>(machineReference, evocoder)));
	return executionReference;
}

std::string ExecutionServer::executeProtocolOnExistingMachine(const std::string & protocolJson, const std::string & machineReference) throw (std::invalid_argument)
{
	ExecutionMachineServer* machineServer = ExecutionMachineServer::GetInstance();

	vector<int> coms;
	shared_ptr<ExecutableMachineGraph> machine = machineServer->getMachine(machineReference);
	coms.push_back(machineServer->getMachineComId(machineReference));

	shared_ptr<ProtocolGraph> protocol(ProtocolGraph::fromJSON(protocolJson));
	shared_ptr<VariableTable> table = make_shared<VariableTable>();

	string executionReference = "execution" + patch::to_string(series.getNextValue());
	protocol->updateReference(executionReference);

	shared_ptr<Mapping> map = make_shared<Mapping>(machine, protocol->getName() + "_" + machine->getName(), coms);
	shared_ptr<EvoCoder> evocoder = make_shared<EvoCoder>(protocol, table, map);

	executionMap.insert(make_pair(executionReference, make_tuple(machineReference, evocoder)));
	return executionReference;
}

std::shared_ptr<EvoCoder> ExecutionServer::getEvoCoder(const std::string & reference) throw(std::invalid_argument)
{
	auto it = executionMap.find(reference);
	if (it != executionMap.end()) {
		return get<1>(it->second);
	}
	else {
		throw(std::invalid_argument("the key " + reference + " does not exists"));
	}
}

std::string ExecutionServer::getMachineReference(const std::string & reference) throw(std::invalid_argument)
{
	auto it = executionMap.find(reference);
	if (it != executionMap.end()) {
		return get<0>(it->second);
	}
	else {
		throw(std::invalid_argument("the key " + reference + " does not exists"));
	}
}
