/*
 * ApplyLight.h
 *
 *  Created on: 28 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_APPLYLIGHT_H_
#define SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_APPLYLIGHT_H_

//boost
#include "boost/shared_ptr.hpp"

//local
#include "../../../../operables/mathematics/MathematicOperable.h"
#include "ContainerOperation.h"

class ApplyLight: public ContainerOperation {
public:
	// Node methods
	ApplyLight();
	ApplyLight(const ApplyLight & node);

	virtual std::string toText();
	virtual void loadNode(const std::string & line)
			throw (std::invalid_argument);
	//
	ApplyLight(int idContainer, boost::shared_ptr<Mapping> mapping,
			int sourceID, boost::shared_ptr<MathematicOperable> wavelength,
			boost::shared_ptr<MathematicOperable> intensity);

	virtual ~ApplyLight();

	virtual void execute();
protected:
	int sourceId;
	boost::shared_ptr<MathematicOperable> wavelength;
	boost::shared_ptr<MathematicOperable> intensity;
};

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_APPLYLIGHT_H_ */
