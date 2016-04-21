/*
 * SetContinousFlow.h
 *
 *  Created on: 23 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONATINER_SETCONTINOUSFLOW_H_
#define SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONATINER_SETCONTINOUSFLOW_H_

#include <string>

//local
#include "../../../../operables/mathematics/MathematicOperable.h"
#include "ContainerOperation.h"

class SetContinousFlow: public ContainerOperation {
public:
	// Node methods
	SetContinousFlow();
	SetContinousFlow(const SetContinousFlow & node);

	virtual std::string toText();
	virtual void loadNode(const std::string & line) throw (invalid_argument);
	//

	SetContinousFlow(int idContainer, boost::shared_ptr<Mapping> mapping, int idSource, int idTarget, boost::shared_ptr<MathematicOperable> rate);
	virtual ~SetContinousFlow();

	virtual void execute();
protected:
	int idSource;
	int idTarget;
	boost::shared_ptr<MathematicOperable> rate;
};

#endif /* SRC_FLUIDCONTROL_PROTOCOLGRAPH_OPERATIONS_CONATINER_SETCONTINOUSFLOW_H_ */
