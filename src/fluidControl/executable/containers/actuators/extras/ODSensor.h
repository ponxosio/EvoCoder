/*
 * ODSensor.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_ODSENSOR_H_
#define SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_ODSENSOR_H_

#include "../Instructable.h"
#include "../Communicable.h"

class ODSensor: public Instructable, Communicable {
public:
	ODSensor(CommandSender* command) :
			Instructable(), Communicable(command) {
	}
	virtual ~ODSensor() {
	}

	virtual std::string getInstructions() = 0;
	virtual double readOd() = 0;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_ODSENSOR_H_ */
