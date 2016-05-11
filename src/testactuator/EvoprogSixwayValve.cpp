/*
 * EvoprogSixwayValve.cpp
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#include "EvoprogSixwayValve.h"

EvoprogSixwayValve::EvoprogSixwayValve(CommandSender* communications,
		int valveNumber) :
		Control(6, communications) {
	this->valveNumber = valveNumber;
	this->lastPos = 0;
}

EvoprogSixwayValve::~EvoprogSixwayValve() {

}

void EvoprogSixwayValve::addConnection(int idSource, int idTraget) {
	if (lastPos <= 6) {
		lastPos += 1;
		containerValveMap.insert(std::make_pair(idTraget, lastPos));
	}
}

void EvoprogSixwayValve::setConnection(int idSource, int idTraget) {
	auto it  = containerValveMap.find(idTraget);
	if (it != containerValveMap.end()) {
		std::string command = "MOVE " + patch::to_string(valveNumber) + " " + patch::to_string(it->second);
		communications->sendString(command);
	}
}

std::string EvoprogSixwayValve::getInstructions() {
	return "";
}
