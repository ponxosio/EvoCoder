/*
 * Temperature.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_TEMPERATURE_H_
#define SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_TEMPERATURE_H_

#include "../Instructable.h"
#include "X:\\codigo\\EvoCoder_Release_v1\\EvoCoder\\src\\fluidControl\\executable\\containers\\actuators\\communications\\CommandSender.h"

class Temperature: public Instructable {
public:
	Temperature(CommandSender* communications) :
			Instructable() {
		this->communications = communications;
	}
	virtual ~Temperature() {
	}

	virtual std::string getInstructions() = 0;
	virtual void apply(double degrees) = 0;
protected:
	CommandSender* communications;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_TEMPERATURE_H_ */
