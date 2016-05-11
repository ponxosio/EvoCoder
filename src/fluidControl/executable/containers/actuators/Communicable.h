/*
 * Communicable.h
 *
 *  Created on: 10 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_COMMUNICABLE_H_
#define SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_COMMUNICABLE_H_

#include "X:\\codigo\\EvoCoder_Release_v1\\EvoCoder\\src\\fluidControl\\executable\\containers\\actuators\\communications\\CommandSender.h"

class Communicable {
public:
	Communicable(CommandSender* communications){
		this->communications = communications;
	}
	virtual ~Communicable(){}

protected:
	CommandSender* communications;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_COMMUNICABLE_H_ */
