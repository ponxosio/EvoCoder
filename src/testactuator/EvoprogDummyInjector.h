/*
 * EvoprogDummyInjector.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef TESTACTUATOR_EVOPROGDUMMYINJECTOR_H_
#define TESTACTUATOR_EVOPROGDUMMYINJECTOR_H_

#include "../fluidControl/executable/containers/actuators/liquids/Injector.h"
#include "../fluidControl/machineGraph/ContainerNodeType.h"
#include "../fluidControl/executable/containers/actuators/communications/CommunicationsInterface.h"

class EvoprogDummyInjector: public Injector {
public:
	EvoprogDummyInjector(int communications);
	virtual ~EvoprogDummyInjector();

	virtual void injectLiquid(double rate);
	virtual std::string getInstructions();
	virtual int getMovementType();
};

#endif /* TESTACTUATOR_EVOPROGDUMMYINJECTOR_H_ */
