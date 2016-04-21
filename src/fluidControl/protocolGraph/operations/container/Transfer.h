/*
 * Transfer.h
 *
 *  Created on: 23 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONATINER_TRANSFER_H_
#define SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONATINER_TRANSFER_H_

#include <string>

//local
#include "../../../../operables/mathematics/MathematicOperable.h"
#include "ContainerOperation.h"

class Transfer: public ContainerOperation {
public:
	//Node methods
	Transfer();
	Transfer(const Transfer & node) ;
	virtual ~Transfer();

	virtual std::string toText();
	virtual void loadNode(const std::string & line) throw (std::invalid_argument);
	//

	Transfer(int idContainer, boost::shared_ptr<Mapping> mapping, int idSource,
			int idTarget, boost::shared_ptr<MathematicOperable> volume);

	virtual void execute();

protected:
	int idSource;
	int idTarget;
	boost::shared_ptr<MathematicOperable> volume;
};

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONATINER_TRANSFER_H_ */
