/*
 * Injector.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_LIQUIDACTUATORS_INJECTOR_H_
#define SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_LIQUIDACTUATORS_INJECTOR_H_

#include "X:\\codigo\\EvoCoder_Release_v1\\EvoCoder\\src\\fluidControl\\executable\\containers\\actuators\\communications\\CommandSender.h"
#include "../Instructable.h"

class Injector: public Instructable {
public:
	Injector(CommandSender* communications) : Instructable() {
		this->communications = communications;
	}
	virtual ~Injector(){}

	virtual void injectLiquid(double rate) = 0;
	virtual std::string getInstructions() = 0;
	virtual int getMovementType() = 0;

protected:
	CommandSender* communications;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_LIQUIDACTUATORS_INJECTOR_H_ */
