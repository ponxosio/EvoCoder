/*
 * ProtocolGraph.h
 *
 *  Created on: 9 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_MACHINEGRAPH_MACHINEGRAPH_H_
#define SRC_FLUIDCONTROL_MACHINEGRAPH_MACHINEGRAPH_H_

#include <string>
#include <memory>
#include <tuple>

//data structed
#include <unordered_map>

//local
#include "../../graph/Graph.h"
#include "../../graph/Edge.h"
#include "ContainerNode.h"
#include "ContainerNodeType.h"

class MachineGraph {
public:
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
		bool vuelta = false;
		try {
			machine->getNode(idContainer);
			vuelta = true;
		} catch (std::invalid_argument& e) {

		}
		return vuelta;
	}

	inline std::shared_ptr<ContainerNode> getContainer(int idContainer) {
		return (machine->getNode(idContainer));
	}

	inline const std::vector<std::tuple<std::vector<std::shared_ptr<ContainerNode>>,std::vector<std::shared_ptr<Edge>>>> & getSubgraphs() {
		return machine->getSubGraphs();
	}

	inline Graph<ContainerNode, Edge>* getGraph() {
		return machine;
	}

protected:
	std::string name;
	Graph<ContainerNode, Edge>* machine;
};

#endif /* SRC_FLUIDCONTROL_MACHINEGRAPH_MACHINEGRAPH_H_ */
