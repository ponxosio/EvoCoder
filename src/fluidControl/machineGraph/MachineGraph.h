/*
 * ProtocolGraph.h
 *
 *  Created on: 9 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_MACHINEGRAPH_MACHINEGRAPH_H_
#define SRC_FLUIDCONTROL_MACHINEGRAPH_MACHINEGRAPH_H_

#include <string>

//data structed
#include <unordered_map>

//local
#include "../../graph/Graph.h"
#include "../../graph/Edge.h"
#include "ContainerNode.h"
#include "ContainerNodeType.h"

class MachineGraph {
public:
	
	typedef Graph<ContainerNode,Edge>::NodeTypePtr ContainerNodePtr;
	typedef Graph<ContainerNode, Edge>::EdgeTypePtr ContainerEdgePtr;

	typedef Graph<ContainerNode, Edge>::NodeVector ContainerNodeVector;
	typedef Graph<ContainerNode, Edge>::EdgeVector ContainerEdgeVector;

	typedef Graph<ContainerNode, Edge>::NodeVectorPtr ContainerNodeVectorPtr;
	typedef Graph<ContainerNode, Edge>::EdgeVectorPtr ContainerEdgeVectorPtr;

	typedef Graph<ContainerNode, Edge>::SubGraphPtr ContainerSubGraphPtr;
	
	MachineGraph(std::string name);
	virtual ~MachineGraph();

	bool addContainer(int idContainer, std::shared_ptr<ContainerNodeType> type, float capacity);
	bool connectContainer(int idSource, int idTarget);

	bool changeContainerType(int idContainer, ContainerType type);
	bool changeMovementType(int idContainer, MovementType type);
	bool addAddon(int idContainer, AddOnsType type);
	bool removeAddon(int idContainer, AddOnsType type);

	bool areConected(int idSource, int idTarget);
	bool hasConections(int idContainer);

	float getVolume(int idContainer);
	bool addVolume(int idContainer, float volume);
	bool extractVolume(int idContainer, float volume);

	void printMachine(const std::string & path);

	/**
	 * return if a certain container already exists in the machine
	 * @param idContainer ID of the container
	 * @return true if the container is already in the machine, false otherwise
	 */
	inline bool existsContainer(int idContainer) {
		return (machine->getNode(idContainer) != NULL);
	}

	inline typename ContainerNodePtr getContainer(int idContainer) {
		return (machine->getNode(idContainer));
	}

	inline typename ContainerSubGraphPtr getSubgraphs() {
		return machine->getSubGraphs();
	}

	inline Graph<ContainerNode, Edge>* getGraph() {
		return machine;
	}

protected:
	std::string name;
	Graph<ContainerNode, Edge>* machine;

	ContainerNodePtr createContainerNode(int idContainer, std::shared_ptr<ContainerNodeType> type,
		float capacity);
	ContainerEdgePtr createContainerEdgePtr(int idSource, int idTarget);
};

#endif /* SRC_FLUIDCONTROL_MACHINEGRAPH_MACHINEGRAPH_H_ */
