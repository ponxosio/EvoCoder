/*
 * EvoprogLight.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef TESTACTUATOR_EVOPROGLIGHT_H_
#define TESTACTUATOR_EVOPROGLIGHT_H_

#include <windows.h>
#include <cmath>

#include "../util/Patch.h"
#include "../fluidControl/executable/containers/actuators/extras/Light.h"
#include "../fluidControl/executable/containers/actuators/communications/CommunicationsInterface.h"

class EvoprogLight: public Light {
public:
	EvoprogLight(int communications, int pinWaveLength, int pinIntensity);
	virtual ~EvoprogLight();

	virtual std::string getInstructions();
	virtual void applyLight(double waveLength, double intensity);
protected:
	int pinWaveLength;
	int pinIntensity;
};

#endif /* TESTACTUATOR_EVOPROGLIGHT_H_ */
