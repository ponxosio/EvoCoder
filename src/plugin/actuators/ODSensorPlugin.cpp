#include "ODSensorPlugin.h"

using namespace boost::python;


ODSensorPlugin::ODSensorPlugin() :
	ODSensor()
{
	this->pluginType = "";
	this->referenceName = "";
}

ODSensorPlugin::ODSensorPlugin(int communications, const std::string & pluginType, const std::vector<std::string>& params) :
	ODSensor(communications)
{
	this->referenceName = "";
	this->pluginType = std::string(pluginType);
	this->params = std::vector<std::string>(params);
}


ODSensorPlugin::~ODSensorPlugin()
{
	if (!referenceName.empty()) {
		PythonEnvironment::GetInstance()->deleteInstance(referenceName);
	}
}

std::string ODSensorPlugin::getInstructions() throw (std::runtime_error)
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

double ODSensorPlugin::readOd() throw (std::runtime_error)
{
	if (referenceName.empty()) {
		referenceName = PythonEnvironment::GetInstance()->makeInstance(this->pluginType, this->params);
	}

	try {
		CommandSender* com = CommunicationsInterface::GetInstance()->getCommandSender(communications);
		double movementType = extract<double>(PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("readOD")(boost::ref(*com)));
		return movementType;
	}
	catch (error_already_set) {
		PyObject *ptype, *pvalue, *ptraceback;
		PyErr_Fetch(&ptype, &pvalue, &ptraceback);

		throw(std::runtime_error("error at python environment " + std::string(PyString_AsString(pvalue))));
	}
}
