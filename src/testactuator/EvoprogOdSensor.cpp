/*
 * EvoprogOdSensor.cpp
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#include "EvoprogOdSensor.h"

EvoprogOdSensor::EvoprogOdSensor(int command, int port) : ODSensor(command){
	this->port = port;
}

EvoprogOdSensor::~EvoprogOdSensor() {
}

std::string EvoprogOdSensor::getInstructions() {
	return "";
}

double EvoprogOdSensor::readOd() throw (std::invalid_argument) {
	std::string command = "READS " + patch::to_string(port);
	CommandSender* com = CommunicationsInterface::GetInstance()->getCommandSender(this->communications);

	com->sendString(command);
	Sleep(50);
	std::string dataString= com->readUntil('\n');

	LOG(DEBUG) << "data received: " << dataString;

	//remove special characters
	dataString.resize(remove_if(dataString.begin(), dataString.end(),[](char x){return iscntrl(x);})-dataString.begin());

	float dataNumeric = -1.0;
	if (!patch::stod(dataNumeric, dataString.c_str())) {
		throw(std::invalid_argument("The returned data sent by the controlled is not a number, is " + dataString));
	}
	return dataNumeric;
}
