#include "TemperaturePlugin.h"

using namespace boost::python;

TemperaturePlugin::TemperaturePlugin() :
	Temperature()
{
	this->pluginType = "";
	this->referenceName = "";
}

TemperaturePlugin::TemperaturePlugin(int communications, const std::string & pluginType, const std::vector<std::string>& params) :
	Temperature(communications)
{
	this->referenceName = "";
	this->pluginType = std::string(pluginType);
	this->params = std::vector<std::string>(params);
}


TemperaturePlugin::~TemperaturePlugin()
{
	if (!referenceName.empty()) {
		PythonEnvironment::GetInstance()->deleteInstance(referenceName);
	}
}

std::string TemperaturePlugin::getInstructions() throw(std::runtime_error)
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

void TemperaturePlugin::apply(double degrees) throw(std::runtime_error)
{
	if (referenceName.empty()) {
		referenceName = PythonEnvironment::GetInstance()->makeInstance(this->pluginType, this->params);
	}

	try {
		CommandSender* com = CommunicationsInterface::GetInstance()->getCommandSender(communications);
		PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("mix")(degrees, boost::ref(*com));
	}
	catch (error_already_set) {
		PyObject *ptype, *pvalue, *ptraceback;
		PyErr_Fetch(&ptype, &pvalue, &ptraceback);

		throw(std::runtime_error("error at python environment " + std::string(PyString_AsString(pvalue))));
	}
}
