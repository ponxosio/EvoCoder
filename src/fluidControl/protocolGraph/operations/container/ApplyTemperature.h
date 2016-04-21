/*
 * ApplyTemperature.h
 *
 *  Created on: 28 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_APPLYTEMPERATURE_H_
#define SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_APPLYTEMPERATURE_H_

//boost
#include "boost/shared_ptr.hpp"

//local
#include "../../../../operables/mathematics/MathematicOperable.h"
#include "ContainerOperation.h"

class ApplyTemperature: public ContainerOperation {
public:
	// Node methods
	ApplyTemperature();
	ApplyTemperature(const ApplyTemperature & node);

	virtual std::string toText();
	virtual void loadNode(const std::string & line)
			throw (std::invalid_argument);
	//
	ApplyTemperature(int containerId, boost::shared_ptr<Mapping>, int sourceId,
			boost::shared_ptr<MathematicOperable> degress);

	virtual ~ApplyTemperature();

	virtual void execute();
protected:
	int sourceId;
	boost::shared_ptr<MathematicOperable> degress;
};

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_APPLYTEMPERATURE_H_ */
