/*
 * Mix.h
 *
 *  Created on: 23 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_MIX_H_
#define SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_MIX_H_

//boost
#include <memory>

//local
#include "../../../operables/mathematics/MathematicOperable.h"
#include "ContainerOperation.h"

class Mix: public ContainerOperation {
public:
	// Node methods
	Mix();
	Mix(const Mix & node);

	virtual std::string toText();
	virtual void loadNode(const std::string & line) throw (invalid_argument);
	//

	Mix(int idConatiner, std::shared_ptr<Mapping> mapping, int idSource1,
			int idSource2, int idTarget,
			std::shared_ptr<MathematicOperable> volume1,
			std::shared_ptr<MathematicOperable> volume2);

	virtual ~Mix();

	virtual void execute();
protected:
	int idSource1;
	int idSource2;
	int idTarget;
	std::shared_ptr<MathematicOperable> volume1;
	std::shared_ptr<MathematicOperable> volume2;
};

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONTAINER_MIX_H_ */
