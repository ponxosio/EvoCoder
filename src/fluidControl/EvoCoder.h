/*
 * EvoCoder.h
 *
 *  Created on: 6 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EVOCODER_H_
#define SRC_FLUIDCONTROL_EVOCODER_H_

/***** OPERATION MODES *****/
#define SCHEDULE		0
#define	EXEC_GENERAL	1
#define EXEC_EP			2
#define DESIGN_TEST		3

/**** TIME VARIABLE ****/
#define TIME_VARIABLE "actualTime"

//includes
#include <algorithm>
#include <string>
#include <stdexcept>
#include <ios>

//data structures
#include <queue>
#include <vector>

//lib
#include "../../lib/easylogging++.h"

//boost
#include <memory>

//local
#include "../util/Utils.h"
#include "Mapping.h"
#include "machineGraph/MachineGraph.h"
#include "executable/ExecutableMachineGraph.h"
#include "executable/containers/actuators/communications/CommunicationsInterface.h"
#include "../protocolGraph/ProtocolGraph.h"
#include "../protocolGraph/OperationNode.h"
#include "../protocolGraph/operations/LoopNode.h"
#include "../protocolGraph/operations/DivergeNode.h"


class EvoCoder {
public:
	/**
	 *
	 * @param protocol graph with the protocol being executed
	 * @param machine graph with the description of the machine where the protocol will
	 * be executed
	 * @param table table where the values of the variable of the protocol will be stored
	 * @param name name of the portocol
	 */
	EvoCoder(ProtocolGraph* protocol,
			std::shared_ptr<VariableTable> table, Mapping* mapping);
	virtual ~EvoCoder();

	/**
	 * Tries to execute the protocol on the machine
	 * @return true if all was correct, false otherwise
	 */
	bool exec_general() throw (std::invalid_argument);
	bool exec_ep() throw (std::invalid_argument);

	bool sketcher();
	/**
	 * Tries to execute a test of the protocol on the machine
	 * @return true if all was correct, false otherwise
	 */
	bool test() throw (std::invalid_argument);

protected:
	/**
	 * protocol graph with the protocol being executed
	 */
	ProtocolGraph* protocol;
	/**
	 * Mapping between the sketch machine and the real one
	 */
	Mapping* mapping;
	/**
	 * table table where the values of the variable of the protocol will be stored
	 */
	std::shared_ptr<VariableTable> table;
	/**
	 * actual node of the protocol
	 */
	OperationNode* actual;

	void initilizeTime();
	void addAvailableEdges(std::queue<OperationNode*>* nodes);
	bool isLast(std::vector<std::pair<DivergeNode*,bool>>* branchChosen, DivergeNode* node);
	bool isPresent(
			std::vector<std::pair<DivergeNode*, bool>>* branchChosen,
			DivergeNode* node,
			std::pair<DivergeNode*, bool> & returned);

	//exec methods
	bool exec();
	bool execRelaxed();
	void execRelaxed_newBranch(OperationNode* start,
			std::vector<LoopNode*> loopsBeingExecuted,
			std::queue<OperationNode*> pending,
			std::vector<std::pair<DivergeNode*,bool>> branchChosen);

	void execRelaxed_ProcessNode(std::vector<LoopNode*>* loopsBeingExecuted,
			std::queue<OperationNode*>* pending,
			std::vector<std::pair<DivergeNode*,bool>>* branchChosen);
	void execRelaxed_ProcessLoopNode(LoopNode* node,
			std::vector<LoopNode*>* loopsBeingExecuted,
			std::queue<OperationNode*>* pending);
	void execRelaxed_ProcessDivergeNode(DivergeNode* node,
			std::vector<LoopNode*>* loopsBeingExecuted,
			std::queue<OperationNode*>* pending,
			std::vector<std::pair<DivergeNode*,bool>>* branchChosen);

};

#endif /* SRC_FLUIDCONTROL_EVOCODER_H_ */
