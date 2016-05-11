/*
 * DivergentSwitch.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_DIVERGENTSWITCH_H_
#define SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_DIVERGENTSWITCH_H_

//boost
#include <boost/shared_ptr.hpp>

#include "../../executable/containers/ExecutableContainerNode.h"
#include "actuators/liquids/Control.h"
#include "actuators/liquids/Extractor.h"

class DivergentSwitch: public ExecutableContainerNode {
public:
	//methods of being node
	DivergentSwitch();
	DivergentSwitch(const DivergentSwitch & node);

//	virtual std::string toText();
	virtual void loadNode(const std::string & line)
			throw (std::invalid_argument);
	//
	DivergentSwitch(int idConatiner, float capacity,
			boost::shared_ptr<Extractor> extract, boost::shared_ptr<Control> control);

	virtual ~DivergentSwitch();

	virtual void receiveLiquid(int source, int target, double rate)
			throw (std::invalid_argument);
	virtual void extractLiquid(int source, int target, double rate)
			throw (std::invalid_argument);
	virtual void connectContainer(int source, int target);
protected:
	boost::shared_ptr<Extractor> extract;
	boost::shared_ptr<Control> control;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_DIVERGENTSWITCH_H_ */
