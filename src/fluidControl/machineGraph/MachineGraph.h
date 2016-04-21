/*
 * ProtocolGraph.h
 *
 *  Created on: 9 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_MACHINEGRAPH_MACHINEGRAPH_H_
#define SRC_FLUIDCONTROL_MACHINEGRAPH_MACHINEGRAPH_H_

#include <string>

#include "../../graph/Graph.h"
#include "../../graph/Edge.h"
#include "../machineGraph/ContainerNode.h"

class MachineGraph {
public:
	MachineGraph(std::string name);
	virtual ~MachineGraph();

	bool addContainer(int idContainer, NodeType type, float capacity);
	bool connectContainer(int idSource, int idTarget);
	bool changeContainerType(int idContainer, NodeType type);

	bool areConected(int idSource, int idTarget);
	bool hasConections(int idContainer);

	float getVolume(int idContainer);
	bool addVolume(int idContainer, float volume);
	bool extractVolume(int idContainer, float volume);

	/**
	 * return if a certain container already exists in the machine
	 * @param idContainer ID of the container
	 * @return true if the container is already in the machine, false otherwise
	 */
	inline bool existsContainer(int idContainer) {
		return (machine->getNode(idContainer) != NULL);
	}

	inline ContainerNode* getContainer(int idContainer) {
		return (machine->getNode(idContainer));
	}

	void printMachine(const std::string & path);

protected:
	std::string name;
	Graph<ContainerNode, Edge>* machine;
};

#endif /* SRC_FLUIDCONTROL_MACHINEGRAPH_MACHINEGRAPH_H_ */
