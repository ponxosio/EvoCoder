/*
 * EvoprogLight.cpp
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#include "EvoprogLight.h"

EvoprogLight::EvoprogLight(CommandSender* communications, int pinWaveLength,
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
	this->communications->sendString(commandIntensity);
	this->communications->sendString(commandWave);
	Sleep(60);
	this->communications->receiveString();
}
