/*
 * Temperature.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_TEMPERATURE_H_
#define SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_TEMPERATURE_H_

#include "../Instructable.h"

class Temperature: public Instructable {
public:
	Temperature(int communications) :
			Instructable() {
		this->communications = communications;
	}
	virtual ~Temperature() {
	}

	virtual std::string getInstructions() = 0;
	virtual void apply(double degrees) = 0;
protected:
	int communications;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_TEMPERATURE_H_ */
