/*
 * EvoprogMixer.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef TESTACTUATOR_EVOPROGMIXER_H_
#define TESTACTUATOR_EVOPROGMIXER_H_

#include <cmath>
#include <windows.h>

#include "../fluidControl/executable/containers/actuators/extras/Mixer.h"
#include "../util/Patch.h"

class EvoprogMixer: public Mixer {
public:
	EvoprogMixer(CommandSender* communications, int pinNumber);
	virtual ~EvoprogMixer();

	virtual std::string getInstructions();
		virtual void mix(double intensity);
protected:
	int pinNumber;
};

#endif /* TESTACTUATOR_EVOPROGMIXER_H_ */
