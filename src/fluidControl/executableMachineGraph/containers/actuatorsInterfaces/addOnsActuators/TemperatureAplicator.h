/*
 * TemperatureAplicator.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_ADDONSACTUATORS_TEMPERATUREAPLICATOR_H_
#define SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_ADDONSACTUATORS_TEMPERATUREAPLICATOR_H_

#include "../Instructable.h"

class TemperatureAplicator: public Instructable {
public:
	virtual ~TemperatureAplicator(){}

	virtual void applyTemperature(double degrees) = 0;
	virtual std::string getInstructions() = 0;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_ADDONSACTUATORS_TEMPERATUREAPLICATOR_H_ */
