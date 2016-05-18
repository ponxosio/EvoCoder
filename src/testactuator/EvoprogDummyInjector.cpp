/*
 * EvoprogDummyInjector.cpp
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#include "EvoprogDummyInjector.h"

EvoprogDummyInjector::EvoprogDummyInjector(int communications) : Injector(communications) {
}

EvoprogDummyInjector::~EvoprogDummyInjector() {
	// TODO Auto-generated destructor stub
}

void EvoprogDummyInjector::injectLiquid(double rate) {
}

std::string EvoprogDummyInjector::getInstructions() {
	return "";
}

int EvoprogDummyInjector::getMovementType() {
	return MovementType::irrelevant;
}
