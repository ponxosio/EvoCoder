/*
 * Control.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_LIQUIDACTUATORS_CONTROL_H_
#define SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_LIQUIDACTUATORS_CONTROL_H_

#include "../Instructable.h"
#include "../Communicable.h"

class Control: public Instructable, Communicable {
public:
	Control(int maxConexiones, CommandSender* communications) :
			Communicable(communications) {
		this->maxConexiones = maxConexiones;
	}
	virtual ~Control(){}

	virtual void addConnection(int idSource, int idTraget) = 0;
	virtual void setConnection(int idSource, int idTraget) = 0;
	virtual std::string getInstructions() = 0;
protected:
	int maxConexiones;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_LIQUIDACTUATORS_CONTROL_H_ */
