/*
 * Mixer.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_MIXER_H_
#define SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_MIXER_H_

#include "../Instructable.h"

class Mixer: public Instructable {
public:
	Mixer(int communications) :
			Instructable() {
		this->communications = communications;
	}
	virtual ~Mixer(){}

	virtual std::string getInstructions() = 0;
	virtual void mix(double intensity) = 0;
protected:
	int communications;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_MIXER_H_ */
