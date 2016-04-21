/*
 * LoadContainer.h
 *
 *  Created on: 5 de abr. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_LOADCONTAINEROPERATION_H_
#define SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_LOADCONTAINEROPERATION_H_

//boost
#include <boost/shared_ptr.hpp>

//local
#include "../../../../util/Utils.h"
#include "../../../../operables/mathematics/MathematicOperable.h"
#include "ContainerOperation.h"

class LoadContainerOperation: public ContainerOperation {
public:
	//methods for node
	LoadContainerOperation();
	LoadContainerOperation(const LoadContainerOperation & obj);

	virtual std::string toText();
	virtual void loadNode(const std::string & line)	throw (std::invalid_argument);
	//
	LoadContainerOperation(int idConatiner, boost::shared_ptr<Mapping> executable, int idSource, boost::shared_ptr<MathematicOperable> value);

	virtual ~LoadContainerOperation();

	virtual void execute();
protected:
	int idSource;
	boost::shared_ptr<MathematicOperable> value;
};

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_LOADCONTAINEROPERATION_H_ */
