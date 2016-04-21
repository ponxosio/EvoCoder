/*
 * TimeStep.h
 *
 *  Created on: 28 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_TIMESTEP_H_
#define SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_TIMESTEP_H_

//boost
#include <boost/shared_ptr.hpp>

//local
#include "../../../../operables/mathematics/VariableEntry.h"
#include "ContainerOperation.h"

class TimeStep: public ContainerOperation {
public:
	// Node methods
	TimeStep();
	TimeStep(const TimeStep & node);

	virtual std::string toText();
	virtual void loadNode(const std::string & line) throw (invalid_argument);
	//
	TimeStep(int containerId, boost::shared_ptr<Mapping> mapping, boost::shared_ptr<VariableEntry> receiver);

	virtual ~TimeStep();

	virtual void execute();
protected:
	boost::shared_ptr<VariableEntry> receiver;
};

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_TIMESTEP_H_ */
