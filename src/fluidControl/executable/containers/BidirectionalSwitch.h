/*
 * BidirectionalSwitch.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_BIDIRECTIONALSWITCH_H_
#define SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_BIDIRECTIONALSWITCH_H_

#include <stdexcept>

// boost
#include <boost/shared_ptr.hpp>

//local
#include "../../executable/containers/ExecutableContainerNode.h"
#include "actuators/liquids/Control.h"
#include "actuators/liquids/Extractor.h"
#include "actuators/liquids/Injector.h"

class BidirectionalSwitch: public ExecutableContainerNode {
public:
	//methods of being node
	BidirectionalSwitch();
	BidirectionalSwitch(const BidirectionalSwitch & node);

	virtual std::string toText();
	virtual void loadNode(const std::string & line)
			throw (std::invalid_argument);
	//
	BidirectionalSwitch(int idContainer, float capacity,
			boost::shared_ptr<Extractor> extract,
			boost::shared_ptr<Injector> insert,
			boost::shared_ptr<Control> controlIN,
			boost::shared_ptr<Control> controlOUT);

	virtual ~BidirectionalSwitch();

	virtual void receiveLiquid(int source, int target, double rate)
			throw (std::invalid_argument);
	virtual void extractLiquid(int source, int target, double rate)
			throw (std::invalid_argument);
	virtual void connectContainer(int source, int target);
protected:
	boost::shared_ptr<Extractor> extract;
	boost::shared_ptr<Injector> insert;
	boost::shared_ptr<Control> controlIN;
	boost::shared_ptr<Control> controlOUT;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_BIDIRECTIONALSWITCH_H_ */
