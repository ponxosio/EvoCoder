/*
 * EvoprogDiscretePump.cpp
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#include "EvoprogDiscretePump.h"

EvoprogDiscretePump::EvoprogDiscretePump(CommandSender* command,
		int pinNumber) : Extractor(command){
	this->pinNumber = pinNumber;
}

EvoprogDiscretePump::~EvoprogDiscretePump() {
}

void EvoprogDiscretePump::extractLiquid(double rate) {
	std::string command = "DIO " + patch::to_string(pinNumber) + " "
			+ patch::to_string(rate > 0 ? 1 : 0);
	this->communications->sendString(command);
	Sleep(60);
	this->communications->receiveString();
}

std::string EvoprogDiscretePump::getInstructions() {
	return "";
}

int EvoprogDiscretePump::getMovementType() {
	return MovementType::discrete;
}
