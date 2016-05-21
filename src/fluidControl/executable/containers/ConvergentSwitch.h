/*
 * ConvergentSwitch.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_CONVERGENTSWITCH_H_
#define SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_CONVERGENTSWITCH_H_

// boost
#include <memory>

//local
#include "../../executable/containers/ExecutableContainerNode.h"
#include "actuators/liquids/Control.h"
#include "actuators/liquids/Injector.h"

class ConvergentSwitch: public ExecutableContainerNode {
public:
	//methods of being node
	ConvergentSwitch();
	ConvergentSwitch(const ConvergentSwitch & node);

	//virtual std::string toText();
	virtual void loadNode(const std::string & line)
			throw (std::invalid_argument);
	//
	ConvergentSwitch(int idConatiner, float capacity,
			std::shared_ptr<Injector> insert,
			std::shared_ptr<Control> control);

	virtual ~ConvergentSwitch();

	virtual void setPositionInject(int source, int target);
	virtual void setPositionExtract(int source, int target);
	virtual void receiveLiquid(double rate) throw (std::invalid_argument);
	virtual void extractLiquid(double rate) throw (std::invalid_argument);
	virtual void connectContainer(int source, int target);
protected:
	std::shared_ptr<Injector> insert;
	std::shared_ptr<Control> control;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_CONVERGENTSWITCH_H_ */
