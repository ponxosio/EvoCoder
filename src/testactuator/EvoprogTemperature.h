/*
 * EvoprogTemperature.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef TESTACTUATOR_EVOPROGTEMPERATURE_H_
#define TESTACTUATOR_EVOPROGTEMPERATURE_H_

#include <windows.h>
#include <cmath>

#include "../util/Patch.h"
#include "../fluidControl/executable/containers/actuators/extras/Temperature.h"

class EvoprogTemperature: public Temperature {
public:
	EvoprogTemperature(CommandSender* communications, int pinNumber);
	virtual ~EvoprogTemperature();

	virtual std::string getInstructions();
	virtual void apply(double degrees);
protected:
	int pinNumber;
};

#endif /* TESTACTUATOR_EVOPROGTEMPERATURE_H_ */
