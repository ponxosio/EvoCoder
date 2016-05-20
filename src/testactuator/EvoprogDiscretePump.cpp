/*
 * EvoprogDiscretePump.cpp
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#include "EvoprogDiscretePump.h"

EvoprogDiscretePump::EvoprogDiscretePump(int command,
		int pinNumber) : Extractor(command){
	this->pinNumber = pinNumber;
}

EvoprogDiscretePump::~EvoprogDiscretePump() {
}

void EvoprogDiscretePump::extractLiquid(double rate) {
	std::string command = "DIO " + patch::to_string(pinNumber) + " "
			+ patch::to_string(rate > 0 ? 1 : 0);
	CommandSender* com = CommunicationsInterface::GetInstance()->getCommandSender(this->communications);
	com->sendString(command);
	Sleep(60);
	com->synch();
}

std::string EvoprogDiscretePump::getInstructions() {
	return "";
}

int EvoprogDiscretePump::getMovementType() {
	return MovementType::discrete;
}
