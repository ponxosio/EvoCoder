/*
 * InletContainer.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_INLETCONTAINER_H_
#define SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_INLETCONTAINER_H_

//boost
#include <memory>

//local
#include "../../executable/containers/ExecutableContainerNode.h"
#include "actuators/liquids/Extractor.h"


class InletContainer: public ExecutableContainerNode {
public:
	//methods of being node
	InletContainer();
	InletContainer(const InletContainer & node);

	//virtual std::string toText();
	virtual void loadNode(const std::string & line)
			throw (std::invalid_argument);
	//
	InletContainer(int idConatiner, float capacity, std::shared_ptr<Extractor> ext);

	virtual ~InletContainer();

	virtual void setPositionInject(int source, int target);
	virtual void setPositionExtract(int source, int target);
	virtual void receiveLiquid(double rate) throw (std::invalid_argument);
	virtual void extractLiquid(double rate) throw (std::invalid_argument);
	virtual void connectContainer(int source, int target);
protected:
	std::shared_ptr<Extractor> ext;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_INLETCONTAINER_H_ */
