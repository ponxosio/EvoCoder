/*
 * EvoprogMixer.cpp
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#include "EvoprogMixer.h"

EvoprogMixer::EvoprogMixer(int communications, int pinNumber) : Mixer(communications) {
	this->pinNumber = pinNumber;
}

EvoprogMixer::~EvoprogMixer() {

}

std::string EvoprogMixer::getInstructions() {
	return "";
}

void EvoprogMixer::mix(double intensity) {
	std::string command = "PWD " + patch::to_string(pinNumber) + " "
			+ patch::to_string(
					fabs(intensity) > 255 ? 255 : round(fabs(intensity)));
	CommandSender* com = CommunicationsInterface::GetInstance()->getCommandSender(this->communications);
	com->sendString(command);
	Sleep(60);
	com->synch();
}
