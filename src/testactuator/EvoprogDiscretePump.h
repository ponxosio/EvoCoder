/*
 * EvoprogDiscretePump.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef TESTACTUATOR_EVOPROGDISCRETEPUMP_H_
#define TESTACTUATOR_EVOPROGDISCRETEPUMP_H_

#include "../fluidControl/executable/containers/actuators/liquids/Extractor.h"
#include "../fluidControl/machineGraph/ContainerNodeType.h"

class EvoprogDiscretePump: public Extractor {
public:
	EvoprogDiscretePump(CommandSender* command, int pinNumber);
	virtual ~EvoprogDiscretePump();

	virtual void extractLiquid(double rate);
	virtual std::string getInstructions();
	virtual int getMovementType();
protected:
	int pinNumber;
};

#endif /* TESTACTUATOR_EVOPROGDISCRETEPUMP_H_ */
