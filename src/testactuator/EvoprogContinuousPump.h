/*
 * EvoprogContinuousPump.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef TESTACTUATOR_EVOPROGCONTINUOUSPUMP_H_
#define TESTACTUATOR_EVOPROGCONTINUOUSPUMP_H_

#include "../../lib/easylogging++.h"

#include "../fluidControl/executable/containers/actuators/liquids/Extractor.h"
#include "../fluidControl/machineGraph/ContainerNodeType.h"

class EvoprogContinuousPump: public Extractor {
public:
	EvoprogContinuousPump(CommandSender* communications, int pinNumber);
	virtual ~EvoprogContinuousPump();

	virtual void extractLiquid(double rate);
	virtual std::string getInstructions();
	virtual int getMovementType();

protected:
	int pinNumber;
};

#endif /* TESTACTUATOR_EVOPROGCONTINUOUSPUMP_H_ */
