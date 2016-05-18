/*
 * ODSensor.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_ODSENSOR_H_
#define SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_ODSENSOR_H_

#include <stdexcept>

#include "../Instructable.h"

class ODSensor: public Instructable {
public:
	ODSensor(int communications) :
			Instructable() {
		this->communications = communications;
	}
	virtual ~ODSensor() {
	}

	virtual std::string getInstructions() = 0;
	virtual double readOd() throw (std::invalid_argument) = 0;
protected:
	int communications;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_ODSENSOR_H_ */
