#include "ExtractorPlugin.h"

using namespace boost::python;

ExtractorPlugin::ExtractorPlugin() : 
	Extractor()
{
	this->pluginType = "";
	this->referenceName = "";
}

ExtractorPlugin::ExtractorPlugin(int communications, const std::string & pluginType, const std::vector<std::string>& params) : 
	Extractor(communications)
{
	this->pluginType = std::string(pluginType);
	this->params = std::vector<std::string>(params);
	this->referenceName = "";
}

ExtractorPlugin::~ExtractorPlugin()
{
	if (!referenceName.empty()) {
		PythonEnvironment::GetInstance()->deleteInstance(referenceName);
	}
}

void ExtractorPlugin::extractLiquid(double rate) throw (std::runtime_error)
{
	if (referenceName.empty()) {
		referenceName = PythonEnvironment::GetInstance()->makeInstance(this->pluginType, this->params);
	}

	try {
		CommandSender* com = CommunicationsInterface::GetInstance()->getCommandSender(communications);
		PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("extractLiquid")(rate, boost::ref(*com));
	}
	catch (error_already_set) {
		PyObject *ptype, *pvalue, *ptraceback;
		PyErr_Fetch(&ptype, &pvalue, &ptraceback);

		throw(std::runtime_error("error at python environment " + std::string(PyString_AsString(pvalue))));
	}
	
}

std::string ExtractorPlugin::getInstructions() throw (std::runtime_error) {
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

int ExtractorPlugin::getMovementType() throw (std::runtime_error)
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
