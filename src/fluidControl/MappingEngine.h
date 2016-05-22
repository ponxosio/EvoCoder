/*
 * MappingEngine.h
 *
 *  Created on: 12 de may. de 2016
 *      Author: angel
 */

#ifndef FLUIDCONTROL_MAPPINGENGINE_H_
#define FLUIDCONTROL_MAPPINGENGINE_H_

#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>
#include <queue>

#include <memory>

#include "../util/Patch.h"
#include "../util/Utils.h"
#include "../util/ContainersUtils.h"
#include "../graph/Edge.h"
#include "../graph/Flow.h"
#include "../graph/FlowPtrComparator.h"
#include "../fluidControl/machineGraph/MachineGraph.h"
#include "../fluidControl/executable/ExecutableMachineGraph.h"

typedef std::pair<std::vector<ContainerNode*>*, std::vector<Edge*>*> SubGraphSketch;
typedef std::pair<std::vector<ExecutableContainerNode*>*, std::vector<Edge*>*> SubGraphMachine;
typedef std::priority_queue<Flow<Edge>, vector<Flow<Edge>>,FlowPtrComparator<Edge>> FlowsHeap;

class MappingEngine {
public:
	MappingEngine(MachineGraph* sketch,	ExecutableMachineGraph* machine);
	virtual ~MappingEngine();

	bool startMapping();

	Flow<Edge>* getMappedEdge(Edge* skectchEdge)throw(std::invalid_argument);
	int getMappedContainerId(int sketchContainerId) throw(std::invalid_argument);
protected:
	std::unordered_map<int,int>* containersMap;
	std::unordered_map<int,int>* numberSolutionsMap;
	std::unordered_map<std::pair<int,int>, Flow<Edge>*, PairIntIntHashFunction>* edgeFlowMap;

	MachineGraph* sketch;
	ExecutableMachineGraph* machine;

	bool trySubgraph(std::vector<SubGraphSketch>& sketchSubgraphs, std::vector<SubGraphMachine>* machineSubgraphs);
	bool mapSubgraph(std::vector<Edge*>& edges, std::vector<ExecutableContainerNode*>* machineNodes);

	void addSolution(Edge* edge, const Flow<Edge> & flow) throw(std::invalid_argument);
	void removeSolution(Edge* edge);
	void setNodesUsed(const Flow<Edge> & flow);
	void unsetNodesUsed(const Flow<Edge> & flow);

	FlowsHeap getAvailableFlows(Edge* actual, std::vector<ExecutableContainerNode*>* machineNodes);

	inline bool isMapped(int idConatiner) {
		return (containersMap->find(idConatiner) != containersMap->end());
	}
};

#endif /* FLUIDCONTROL_MAPPINGENGINE_H_ */
