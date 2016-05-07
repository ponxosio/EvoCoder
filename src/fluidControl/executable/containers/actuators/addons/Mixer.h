/*
 * Mixer.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_ADDONSACTUATORS_MIXER_H_
#define SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_ADDONSACTUATORS_MIXER_H_

#include "../Instructable.h"

class Mixer: public Instructable {
public:
	Mixer(){}
	virtual ~Mixer(){}

	virtual void setIntensity(double rate) = 0;
	virtual std::string getInstructions() = 0;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_ADDONSACTUATORS_MIXER_H_ */
