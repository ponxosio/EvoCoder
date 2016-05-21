/*
 * MeasureOD.h
 *
 *  Created on: 28 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_MEASUREOD_H_
#define SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_MEASUREOD_H_

//boost
#include <memory>

//local
#include "../../../operables/mathematics/VariableEntry.h"
#include "ContainerOperation.h"

class MeasureOD: public ContainerOperation {
public:
	// Node methods
	MeasureOD();
	MeasureOD(const MeasureOD & node);

	virtual std::string toText();
	virtual void loadNode(const std::string & line) throw (invalid_argument);
	//
	MeasureOD(int containerId, std::shared_ptr<Mapping> mapping, int sourceId, std::shared_ptr<VariableEntry> receiver);

	virtual ~MeasureOD();

	virtual void execute();
protected:
	int sourceId;
	std::shared_ptr<VariableEntry> receiver;
};

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_MEASUREOD_H_ */
