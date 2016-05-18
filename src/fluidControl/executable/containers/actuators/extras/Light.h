/*
 * Light.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_LIGHT_H_
#define SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_LIGHT_H_

#include "../Instructable.h"

class Light: public Instructable {
public:
	Light(int communications) :
			Instructable() {
		this->communications = communications;
	}
	virtual ~Light() {
	}

	virtual std::string getInstructions() = 0;
	virtual void applyLight(double waveLength, double intensity) = 0;
protected:
	int communications;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_LIGHT_H_ */
