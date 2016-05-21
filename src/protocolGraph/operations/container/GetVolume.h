/*
 * GetVolume.h
 *
 *  Created on: 28 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_GETVOLUME_H_
#define SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_GETVOLUME_H_

//boost
#include <boost/shared_ptr.hpp>

//local
#include "../../../operables/mathematics/VariableEntry.h"
#include "ContainerOperation.h"

class GetVolume: public ContainerOperation {
public:
	// Node methods
	GetVolume();
	GetVolume(const GetVolume & node);

	virtual std::string toText();
	virtual void loadNode(const std::string & line) throw (invalid_argument);
	//
	GetVolume(int containerId, boost::shared_ptr<Mapping> mapping, int sourceId,
			boost::shared_ptr<VariableEntry> receiver);

	virtual ~GetVolume();

	virtual void execute();
protected:
	int sourceId;
	boost::shared_ptr<VariableEntry> receiver;
};

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_GETVOLUME_H_ */
