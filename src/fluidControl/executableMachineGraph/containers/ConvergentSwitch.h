/*
 * ConvergentSwitch.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_CONVERGENTSWITCH_H_
#define SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_CONVERGENTSWITCH_H_

// boost
#include <boost/shared_ptr.hpp>

//local
#include "ExecutableContainerNode.h"
#include "actuatorsInterfaces/liquidActuators/Injector.h"
#include "actuatorsInterfaces/liquidActuators/Control.h"

class ConvergentSwitch: public ExecutableContainerNode {
public:
	//methods of being node
	ConvergentSwitch();
	ConvergentSwitch(const ConvergentSwitch & node);

	virtual std::string toText();
	virtual void loadNode(const std::string & line)
			throw (std::invalid_argument);
	//
	ConvergentSwitch(int idConatiner, float capacity,
			boost::shared_ptr<Injector> insert,
			boost::shared_ptr<Control> control);

	virtual ~ConvergentSwitch();

	virtual void receiveLiquid(int source, int target, double rate)
			throw (std::invalid_argument);
	virtual void extractLiquid(int source, int target, double rate)
			throw (std::invalid_argument);
	virtual void connectContainer(int source, int target);
protected:
	boost::shared_ptr<Injector> insert;
	boost::shared_ptr<Control> control;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_CONVERGENTSWITCH_H_ */
