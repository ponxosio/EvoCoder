/*
 * ConvergentSwitchInlet.h
 *
 *  Created on: 4 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_CONVERGENTSWITCHINLET_H_
#define SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_CONVERGENTSWITCHINLET_H_

#include <stdexcept>

#include "../../executable/containers/ExecutableContainerNode.h"
//local
#include "../../machineGraph/ContainerNodeType.h"
#include "actuators/liquids/Control.h"
#include "actuators/liquids/Extractor.h"
#include "actuators/liquids/Injector.h"

class ConvergentSwitchInlet: public ExecutableContainerNode {
public:
	//methods of being node
	ConvergentSwitchInlet();
	ConvergentSwitchInlet(const ConvergentSwitchInlet & node);

	virtual std::string toText();
	virtual void loadNode(const std::string & line)
			throw (std::invalid_argument);
	//
	ConvergentSwitchInlet(int idConatiner, float capacity,
			boost::shared_ptr<Injector> insert,
			boost::shared_ptr<Extractor> extractor,
			boost::shared_ptr<Control> control);

	virtual ~ConvergentSwitchInlet();

	virtual void receiveLiquid(int source, int target, double rate)
			throw (std::invalid_argument);
	virtual void extractLiquid(int source, int target, double rate)
			throw (std::invalid_argument);
	virtual void connectContainer(int source, int target);
protected:
	boost::shared_ptr<Injector> insert;
	boost::shared_ptr<Extractor> extractor;
	boost::shared_ptr<Control> control;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_CONVERGENTSWITCHINLET_H_ */
