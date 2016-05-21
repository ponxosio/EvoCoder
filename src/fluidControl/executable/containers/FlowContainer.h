/*
 * FlowContainer.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_FLOWCONTAINER_H_
#define SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_FLOWCONTAINER_H_

#include <stdexcept>

// boost
#include <memory>

//local
#include "../../executable/containers/ExecutableContainerNode.h"
#include "actuators/liquids/Extractor.h"
#include "actuators/liquids/Injector.h"

class FlowContainer: public ExecutableContainerNode {
public:
	//methods of being node
	FlowContainer();
	FlowContainer(const FlowContainer & node);

	//virtual std::string toText();
	virtual void loadNode(const std::string & line)
			throw (std::invalid_argument);
	//
	FlowContainer(int idContainer, float capacity,
			std::shared_ptr<Extractor> extract, std::shared_ptr<Injector> insert);

	virtual ~FlowContainer();

	virtual void setPositionInject(int source, int target);
	virtual void setPositionExtract(int source, int target);
	virtual void receiveLiquid(double rate) throw (std::invalid_argument);
	virtual void extractLiquid(double rate) throw (std::invalid_argument);
	virtual void connectContainer(int source, int target);
protected:
	std::shared_ptr<Extractor> extract;
	std::shared_ptr<Injector> insert;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_FLOWCONTAINER_H_ */
