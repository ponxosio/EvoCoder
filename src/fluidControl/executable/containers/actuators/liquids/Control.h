/*
 * Control.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_LIQUIDACTUATORS_CONTROL_H_
#define SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_LIQUIDACTUATORS_CONTROL_H_

#include "../Instructable.h"
#include "X:\\codigo\\EvoCoder_Release_v1\\EvoCoder\\src\\fluidControl\\executable\\containers\\actuators\\communications\\CommandSender.h"

class Control: public Instructable {
public:
	Control(int maxConexiones, CommandSender* communications) :
			Instructable() {
		this->maxConexiones = maxConexiones;
		this->communications = communications;
	}
	virtual ~Control(){}

	virtual void addConnection(int idSource, int idTraget) = 0;
	virtual void setConnection(int idSource, int idTraget) = 0;
	virtual std::string getInstructions() = 0;
protected:
	int maxConexiones;
	CommandSender* communications;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_LIQUIDACTUATORS_CONTROL_H_ */
