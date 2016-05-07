/*
 * LightAplicator.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_ADDONSACTUATORS_LIGHTAPLICATOR_H_
#define SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_ADDONSACTUATORS_LIGHTAPLICATOR_H_

#include "../Instructable.h"

class LightAplicator: public Instructable {
public:
	LightAplicator(){}
	virtual ~LightAplicator(){}

	virtual void applyLigth(double wavelength, double intensity) = 0;
	virtual std::string getInstructions() = 0;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_ADDONSACTUATORS_LIGHTAPLICATOR_H_ */
