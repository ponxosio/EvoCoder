#include "InjectorPlugin.h"

using namespace boost::python;

InjectorPlugin::InjectorPlugin() :
	Injector()
{
	this->pluginType = "";
	this->referenceName = "";
}

InjectorPlugin::InjectorPlugin(int communications, const std::string & pluginType, const std::vector<std::string>& params) :
	Injector(communications)
{
	this->referenceName = "";
	this->pluginType = std::string(pluginType);
	this->params = std::vector<std::string>(params);
}


InjectorPlugin::~InjectorPlugin()
{
	if (!referenceName.empty()) {
		PythonEnvironment::GetInstance()->deleteInstance(referenceName);
	}
}

void InjectorPlugin::injectLiquid(double rate) throw (std::runtime_error)
{
	try {
		if (referenceName.empty()) {
			referenceName = PythonEnvironment::GetInstance()->makeInstance(this->pluginType, this->params);
		}

		CommandSender* com = CommunicationsInterface::GetInstance()->getCommandSender(communications);
		PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("injectLiquid")(rate, boost::ref(*com));
	}
	catch (std::invalid_argument & e) 
	{
		throw (std::runtime_error(e.what()));
	}
	catch (error_already_set) {
		PyObject *ptype, *pvalue, *ptraceback;
		PyErr_Fetch(&ptype, &pvalue, &ptraceback);

		throw(std::runtime_error("error at python environment " + std::string(PyString_AsString(pvalue))));
	}
}

std::string InjectorPlugin::getInstructions() throw (std::runtime_error)
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

int InjectorPlugin::getMovementType() throw (std::runtime_error)
{
	if (referenceName.empty()) {
		referenceName = PythonEnvironment::GetInstance()->makeInstance(this->pluginType, this->params);
	}

	try {
		int movementType = extract<int>(PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("getMovementType")());
		return movementType;
	}
	catch (error_already_set) {
		PyObject *ptype, *pvalue, *ptraceback;
		PyErr_Fetch(&ptype, &pvalue, &ptraceback);

		throw(std::runtime_error("error at python environment " + std::string(PyString_AsString(pvalue))));
	}
}
