/*
 * EvoprogOdSensor.cpp
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#include "EvoprogOdSensor.h"

EvoprogOdSensor::EvoprogOdSensor(CommandSender* command, int port) : ODSensor(command){
	this->port = port;
}

EvoprogOdSensor::~EvoprogOdSensor() {
}

std::string EvoprogOdSensor::getInstructions() {
	return "";
}

double EvoprogOdSensor::readOd() throw (std::invalid_argument) {
	std::string command = "READS " + patch::to_string(port);
	communications->sendString(command);
	Sleep(100);
	std::string dataString= communications->readUntil('\r');

	float dataNumeric;
	if (patch::stod(dataNumeric, dataString.c_str())) {
		 return dataNumeric;
	} else {
		throw(std::invalid_argument("The returned data sended by the controlled is not a number, is " + dataString));
	}
	return -1.0;
}
