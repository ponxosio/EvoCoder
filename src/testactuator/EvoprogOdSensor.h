/*
 * EvoprogOdSensor.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef TESTACTUATOR_EVOPROGODSENSOR_H_
#define TESTACTUATOR_EVOPROGODSENSOR_H_

#include <windows.h>

#include "../../lib/easylogging++.h"

#include "../fluidControl/executable/containers/actuators/extras/ODSensor.h"
#include "../util/Patch.h"
#include "../fluidControl/executable/containers/actuators/communications/CommunicationsInterface.h"

class EvoprogOdSensor: public ODSensor {
public:
	EvoprogOdSensor(int command, int port);
	virtual ~EvoprogOdSensor();

	virtual std::string getInstructions();
	virtual double readOd() throw (std::invalid_argument);
protected:
	int port;
};

#endif /* TESTACTUATOR_EVOPROGODSENSOR_H_ */
