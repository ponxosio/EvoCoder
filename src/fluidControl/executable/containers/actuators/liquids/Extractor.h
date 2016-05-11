/*
 * Extractor.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_LIQUIDACTUATORS_EXTRACTOR_H_
#define SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_LIQUIDACTUATORS_EXTRACTOR_H_

#include "../Instructable.h"
#include "X:\\codigo\\EvoCoder_Release_v1\\EvoCoder\\src\\fluidControl\\executable\\containers\\actuators\\communications\\CommandSender.h"

class Extractor: public Instructable {
public:
	Extractor(CommandSender* communications) :
			Instructable() {
		this->communications = communications;
	}
	virtual ~Extractor() {
	}

	virtual void extractLiquid(double rate) = 0;
	virtual std::string getInstructions() = 0;
	virtual int getMovementType() = 0;
protected:
	CommandSender* communications;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_ACTUATORSINTERFACES_LIQUIDACTUATORS_EXTRACTOR_H_ */
