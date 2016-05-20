/*
 * EvoprogContinuousPump.cpp
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#include "EvoprogContinuousPump.h"

EvoprogContinuousPump::EvoprogContinuousPump(int communications,
		int pinNumber) :
		Extractor(communications) {
	this->pinNumber = pinNumber;
}

EvoprogContinuousPump::~EvoprogContinuousPump() {
	// TODO Auto-generated destructor stub
}

void EvoprogContinuousPump::extractLiquid(double rate) {
	std::string command = "DIO " + patch::to_string(pinNumber) + " "
			+ patch::to_string(rate > 0 ? 1 : 0);
	CommandSender* com = CommunicationsInterface::GetInstance()->getCommandSender(this->communications);
	com->sendString(command);
	Sleep(60);
	com->synch();
}

std::string EvoprogContinuousPump::getInstructions() {
	return "";
}

int EvoprogContinuousPump::getMovementType() {
	return MovementType::continuous;
}
