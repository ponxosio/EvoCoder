/*
 * EvoprogLight.cpp
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#include "EvoprogLight.h"

EvoprogLight::EvoprogLight(int communications, int pinWaveLength,
		int pinIntensity) : Light(communications) {
	this->pinIntensity = pinIntensity;
	this->pinWaveLength = pinWaveLength;
}

EvoprogLight::~EvoprogLight() {
}

std::string EvoprogLight::getInstructions() {
	return "";
}

void EvoprogLight::applyLight(double waveLength, double intensity) {
	std::string commandWave = "PWD " + patch::to_string(pinWaveLength) + " "
			+ patch::to_string(
					fabs(waveLength) > 255 ? 255 : round(fabs(waveLength)));
	std::string commandIntensity = "PWD " + patch::to_string(pinIntensity) + " "
				+ patch::to_string(
						fabs(intensity) > 255 ? 255 : round(fabs(intensity)));
	CommandSender* com = CommunicationsInterface::GetInstance()->getCommandSender(this->communications);
	com->sendString(commandIntensity);
	com->sendString(commandWave);
	Sleep(60);
	com->synch();
}
