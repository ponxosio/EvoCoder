/*
 * EvoprogTemperature.cpp
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#include "EvoprogTemperature.h"

EvoprogTemperature::EvoprogTemperature(CommandSender* communications,
		int pinNumber) : Temperature(communications) {
	this->pinNumber = pinNumber;
}

EvoprogTemperature::~EvoprogTemperature() {

}

std::string EvoprogTemperature::getInstructions() {
	return "";
}

void EvoprogTemperature::apply(double degrees) {
	std::string command = "PWD " + patch::to_string(pinNumber) + " "
			+ patch::to_string(fabs(degrees) > 255 ? 255 : round(fabs(degrees)));
	this->communications->sendString(command);
	Sleep(60);
	this->communications->receiveString();
}
