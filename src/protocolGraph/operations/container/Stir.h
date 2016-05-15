/*
 * Stir.h
 *
 *  Created on: 4 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_STIR_H_
#define SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_STIR_H_

//boost
#include "boost/shared_ptr.hpp"

//local
#include "../../../operables/mathematics/MathematicOperable.h"
#include "ContainerOperation.h"


class Stir: public ContainerOperation {
public:
	// Node methods
	Stir();
	Stir(const Stir & node);

	virtual std::string toText();
	virtual void loadNode(const std::string & line)
			throw (std::invalid_argument);
	//
	Stir(int containerId, boost::shared_ptr<Mapping> executable, int sourceId,
				boost::shared_ptr<MathematicOperable> intensity);
	virtual ~Stir();

	virtual void execute();
protected:
	int sourceId;
	boost::shared_ptr<MathematicOperable> intensity;
};

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_STIR_H_ */
