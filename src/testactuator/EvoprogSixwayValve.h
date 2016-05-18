/*
 * EvoprogSixwayValve.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef TESTACTUATOR_EVOPROGSIXWAYVALVE_H_
#define TESTACTUATOR_EVOPROGSIXWAYVALVE_H_

#include <windows.h>

#include <tr1/unordered_map>

#include "../fluidControl/executable/containers/actuators/liquids/Control.h"
#include "../util/Patch.h"
#include "../fluidControl/executable/containers/actuators/communications/CommunicationsInterface.h"

class EvoprogSixwayValve: public Control {
public:
	EvoprogSixwayValve(int communications, int valveNumber);
	virtual ~EvoprogSixwayValve();

	virtual void addConnection(int idSource, int idTraget);
	virtual void setConnection(int idSource, int idTraget);
	virtual std::string getInstructions();
protected:
	int valveNumber;
	std::tr1::unordered_map<int, int> containerValveMap;
	int lastPos;

};

#endif /* TESTACTUATOR_EVOPROGSIXWAYVALVE_H_ */
