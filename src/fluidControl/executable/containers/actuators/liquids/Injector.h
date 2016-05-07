/*
 * Injector.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_LIQUIDACTUATORS_INJECTOR_H_
#define SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_LIQUIDACTUATORS_INJECTOR_H_

#include "../../actuators/Instructable.h"

class Injector: public Instructable {
public:
	Injector(){}
	virtual ~Injector(){}

	virtual void injectLiquid(double rate) = 0;
	virtual std::string getInstructions() = 0;
	virtual int getMovementType() = 0;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_LIQUIDACTUATORS_INJECTOR_H_ */
