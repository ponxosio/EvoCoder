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

typedef Graph<ContainerNode, Edge>::SubGraphElem SubGraphSketch;
typedef Graph<ExecutableContainerNode, Edge>::SubGraphElem SubGraphMachine;
typedef std::priority_queue<Flow<Edge>, vector<Flow<Edge>>,FlowPtrComparator<Edge>> FlowsHeap;

class MappingEngine {
public:
	MappingEngine(MachineGraph* sketch,	ExecutableMachineGraph* machine);
	virtual ~MappingEngine();

	bool startMapping();

	Flow<Edge>* getMappedEdge(MachineGraph::ContainerEdgePtr skectchEdge)throw(std::invalid_argument);
	int getMappedContainerId(int sketchContainerId) throw(std::invalid_argument);
protected:
	std::unordered_map<int,int>* containersMap;
	std::unordered_map<int,int>* numberSolutionsMap;
	std::unordered_map<std::pair<int,int>, Flow<Edge>*, PairIntIntHashFunction>* edgeFlowMap;

	MachineGraph* sketch;
	ExecutableMachineGraph* machine;

	/*bool trySubgraph(Graph<ContainerNode, Edge>::SubGraph & sketchSubgraphs, Graph<ExecutableContainerNode, Edge>::SubGraphPtr machineSubgraphs);*/
	bool mapSubgraph(MachineGraph::ContainerEdgeVector& edges, ExecutableMachineGraph::ExecutableContainerNodeVectorPtr machineNodes);

	void addSolution(MachineGraph::ContainerEdgePtr edge, const Flow<Edge> & flow) throw(std::invalid_argument);
	void removeSolution(MachineGraph::ContainerEdgePtr edge);
	void setNodesUsed(const Flow<Edge> & flow);
	void unsetNodesUsed(const Flow<Edge> & flow);

	FlowsHeap getAvailableFlows(ExecutableMachineGraph::ExecutableContainerEdgePtr actual, ExecutableMachineGraph::ExecutableContainerNodeVectorPtr machineNodes);

	inline bool isMapped(int idConatiner) {
		return (containersMap->find(idConatiner) != containersMap->end());
	}
};

#endif /* FLUIDCONTROL_MAPPINGENGINE_H_ */
