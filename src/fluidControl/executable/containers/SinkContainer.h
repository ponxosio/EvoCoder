/*
 * SinkContainer.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_SINKCONTAINER_H_
#define SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_SINKCONTAINER_H_

#include "../../executable/containers/ExecutableContainerNode.h"
#include "actuators/liquids/Injector.h"

class SinkContainer: public ExecutableContainerNode {
public:
	//methods of being node
	SinkContainer();
	SinkContainer(const SinkContainer & node);

	//virtual std::string toText();
	virtual void loadNode(const std::string & line)
			throw (std::invalid_argument);
	//
	SinkContainer(int idContainer, float capacity,
			 std::shared_ptr<Injector> insert);

	virtual ~SinkContainer();

	virtual void setPositionInject(int source, int target);
	virtual void setPositionExtract(int source, int target);
	virtual void receiveLiquid(double rate) throw (std::invalid_argument);
	virtual void extractLiquid(double rate) throw (std::invalid_argument);
	virtual void connectContainer(int source, int target);
protected:
	std::shared_ptr<Injector> insert;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_SINKCONTAINER_H_ */
