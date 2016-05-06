/*
 * DivergentSwitchSink.h
 *
 *  Created on: 4 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_DIVERGENTSWITCHSINK_H_
#define SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_DIVERGENTSWITCHSINK_H_

#include <stdexcept>

// boost
#include <boost/shared_ptr.hpp>

// local
#include "../../machineGraph/ContainerNodeType.h"
#include "ExecutableContainerNode.h"
#include "actuatorsInterfaces/liquidActuators/Injector.h"
#include "actuatorsInterfaces/liquidActuators/Extractor.h"
#include "actuatorsInterfaces/liquidActuators/Control.h"

class DivergentSwitchSink : public ExecutableContainerNode {
public:
	//methods of being node
	DivergentSwitchSink();
	DivergentSwitchSink(const DivergentSwitchSink & node);

	virtual std::string toText();
	virtual void loadNode(const std::string & line)
			throw (std::invalid_argument);
	//
	DivergentSwitchSink(int idConatiner, float capacity,
			boost::shared_ptr<Injector> insert,
			boost::shared_ptr<Extractor> extractor,
			boost::shared_ptr<Control> control);

	virtual ~DivergentSwitchSink();

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

#endif /* SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_DIVERGENTSWITCHSINK_H_ */
