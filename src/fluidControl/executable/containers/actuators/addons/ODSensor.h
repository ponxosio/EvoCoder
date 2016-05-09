/*
 * ODSensor.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_ADDONSACTUATORS_ODSENSOR_H_
#define SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_ADDONSACTUATORS_ODSENSOR_H_

#include "../Instructable.h"

class ODSensor: public Instructable {
public:
	ODSensor(){}
	virtual ~ODSensor(){}

	virtual double readSensor() = 0;
	virtual std::string getInstructions() = 0;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_ADDONSACTUATORS_ODSENSOR_H_ */
