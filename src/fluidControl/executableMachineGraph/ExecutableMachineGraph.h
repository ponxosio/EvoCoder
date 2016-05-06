/*
 * ExecutableMachineGraph.h
 *
 *  Created on: 9 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_EXECUTABLEMACHINEGRAPH_H_
#define SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_EXECUTABLEMACHINEGRAPH_H_

#include <string>
#include <utility>

//data structure
#include <unordered_map>
#include <vector>

//local
#include "../../graph/Graph.h"
#include "containers/ExecutableContainerNode.h"

class ExecutableMachineGraph {
public:
	ExecutableMachineGraph(const std::string & name);
	virtual ~ExecutableMachineGraph();

	void addContainer(ExecutableContainerNode* node);
	ExecutableContainerNode* getContainer(int idConatiner);

	bool connectExecutableContainer(int idSource, int idTarget);

	void printMachine(const std::string & path);
	/**
	 * return if a certain container already exists in the machine
	 * @param idContainer ID of the container
	 * @return true if the container is already in the machine, false otherwise
	 */
	inline bool existsContainer(int idContainer) {
		return (graph->getNode(idContainer) != NULL);
	}

	inline bool areConected(int idSource, int idTarget) {
		return (graph->areConnected(idSource, idTarget));
	}
protected:
	std::string name;
	Graph<ExecutableContainerNode, Edge>* graph;

};

#endif /* SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_EXECUTABLEMACHINEGRAPH_H_ */
