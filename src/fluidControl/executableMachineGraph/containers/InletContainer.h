/*
 * InletContainer.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_INLETCONTAINER_H_
#define SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_INLETCONTAINER_H_

//boost
#include <boost/shared_ptr.hpp>

//local
#include "ExecutableContainerNode.h"
#include "actuatorsInterfaces/liquidActuators/Extractor.h"


class InletContainer: public ExecutableContainerNode {
public:
	//methods of being node
	InletContainer();
	InletContainer(const InletContainer & node);

	virtual std::string toText();
	virtual void loadNode(const std::string & line)
			throw (std::invalid_argument);
	//
	InletContainer(int idConatiner, float capacity, boost::shared_ptr<Extractor> ext);

	virtual ~InletContainer();

	virtual void receiveLiquid(int source, int target, double rate) throw (std::invalid_argument);
	virtual void extractLiquid(int source, int target, double rate) throw (std::invalid_argument);
	virtual void connectContainer(int source, int target);
protected:
	boost::shared_ptr<Extractor> ext;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_INLETCONTAINER_H_ */
