#include "ControlPlugin.h"

using namespace boost::python;

ControlPlugin::ControlPlugin() :
	Control()
{
	this->pluginType = "";
	this->referenceName = "";
}

ControlPlugin::ControlPlugin(int communications, int maxconnections, const std::string & pluginType, const std::vector<std::string>& params) :
	Control(maxconnections, communications)
{
	this->referenceName = "";
	this->pluginType = std::string(pluginType);
	this->params = std::vector<std::string>(params);
	this->params.insert(this->params.begin(), patch::to_string(maxconnections));
}


ControlPlugin::~ControlPlugin()
{
	if (!referenceName.empty()) {
		PythonEnvironment::GetInstance()->deleteInstance(referenceName);
	}
}

void ControlPlugin::addConnection(int idSource, int idTarget) throw (std::runtime_error)
{
	if (referenceName.empty()) {
		referenceName = PythonEnvironment::GetInstance()->makeInstance(this->pluginType, this->params);
	}

	try {
		CommandSender* com = CommunicationsInterface::GetInstance()->getCommandSender(communications);
		PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("addConnection")(idSource, idTarget, boost::ref(*com));
	}
	catch (error_already_set) {
		PyObject *ptype, *pvalue, *ptraceback;
		PyErr_Fetch(&ptype, &pvalue, &ptraceback);

		throw(std::runtime_error("error at python environment " + std::string(PyString_AsString(pvalue))));
	}
}

void ControlPlugin::setConnection(int idSource, int idTarget) throw (std::runtime_error)
{
	if (referenceName.empty()) {
		referenceName = PythonEnvironment::GetInstance()->makeInstance(this->pluginType, this->params);
	}

	try {
		CommandSender* com = CommunicationsInterface::GetInstance()->getCommandSender(communications);
		PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("setConnection")(idSource, idTarget, boost::ref(*com));
	}
	catch (error_already_set) {
		PyObject *ptype, *pvalue, *ptraceback;
		PyErr_Fetch(&ptype, &pvalue, &ptraceback);

		throw(std::runtime_error("error at python environment " + std::string(PyString_AsString(pvalue))));
	}
}

std::string ControlPlugin::getInstructions() throw (std::runtime_error)
{
	if (referenceName.empty()) {
		referenceName = PythonEnvironment::GetInstance()->makeInstance(this->pluginType, this->params);
	}

	try {
		const char* c_str = extract<const char*>(PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("getInstructions")());
		return std::string(c_str);
	}
	catch (error_already_set) {
		PyObject *ptype, *pvalue, *ptraceback;
		PyErr_Fetch(&ptype, &pvalue, &ptraceback);

		throw(std::runtime_error("error at python environment " + std::string(PyString_AsString(pvalue))));
	}
}
