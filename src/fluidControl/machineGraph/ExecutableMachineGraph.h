/*
 * ExecutableMachineGraph.h
 *
 *  Created on: 9 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_MACHINEGRAPH_EXECUTABLEMACHINEGRAPH_H_
#define SRC_FLUIDCONTROL_MACHINEGRAPH_EXECUTABLEMACHINEGRAPH_H_

#include "MachineGraph.h"

class ExecutableMachineGraph: public MachineGraph {
public:
	ExecutableMachineGraph(std::string name);
	virtual ~ExecutableMachineGraph();
};

#endif /* SRC_FLUIDCONTROL_MACHINEGRAPH_EXECUTABLEMACHINEGRAPH_H_ */
