/*
 * GetVolume.h
 *
 *  Created on: 28 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_GETVOLUME_H_
#define SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_GETVOLUME_H_

//boost
#include <memory>

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
	GetVolume(int containerId, std::shared_ptr<Mapping> mapping, int sourceId,
			std::shared_ptr<VariableEntry> receiver);

	virtual ~GetVolume();

	virtual void execute();
protected:
	int sourceId;
	std::shared_ptr<VariableEntry> receiver;
};

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_GETVOLUME_H_ */
