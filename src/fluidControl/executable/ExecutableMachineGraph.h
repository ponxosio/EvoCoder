/*
 * ExecutableMachineGraph.h
 *
 *  Created on: 9 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLE_EXECUTABLEMACHINEGRAPH_H_
#define SRC_FLUIDCONTROL_EXECUTABLE_EXECUTABLEMACHINEGRAPH_H_

#include <string>
#include <stdexcept>

 //vector
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

//local
#include "../../util/Patch.h"
#include "../../util/Utils.h"
#include "../../util/ContainersUtils.h"
#include "../../graph/Graph.h"
#include "../../graph/Edge.h"
#include "../../graph/Flow.h"
#include "../../graph/FlowPtrComparator.h"
#include "../machineGraph/ContainerNodeType.h"
#include "containers/ExecutableContainerNode.h"

class ExecutableMachineGraph {
public:
	//TYPE DEFS
	typedef Graph<ExecutableContainerNode, Edge>::NodeTypePtr ExecutableContainerNodePtr;
	typedef Graph<ExecutableContainerNode, Edge>::EdgeTypePtr ExecutableContainerEdgePtr;

	typedef Graph<ExecutableContainerNode, Edge>::NodeVector ExecutableContainerNodeVector;
	typedef Graph<ExecutableContainerNode, Edge>::EdgeVector ExecutableContainerEdgeVector;

	typedef Graph<ExecutableContainerNode, Edge>::NodeVectorPtr ExecutableContainerNodeVectorPtr;
	typedef Graph<ExecutableContainerNode, Edge>::EdgeVectorPtr ExecutableContainerEdgeVectorPtr;

	typedef Graph<ExecutableContainerNode, Edge>::SubGraphPtr ExecutableContainerSubGraphPtr;

	typedef std::priority_queue<Flow<Edge>, vector<Flow<Edge>>, FlowPtrComparator<Edge>> FlowHeap;
	//


	ExecutableMachineGraph(const std::string & name);
	virtual ~ExecutableMachineGraph();

	void addContainer(ExecutableContainerNodePtr node);
	ExecutableContainerNodePtr getContainer(int idConatiner);

	bool connectExecutableContainer(int idSource, int idTarget);

	void printMachine(const std::string & path);

	FlowHeap getAvailableFlows(
		const ContainerNodeType & tipoIni,
		const ContainerNodeType & tipofin,
		const ExecutableContainerNodeVector & subgraph);
	FlowHeap getAvailableFlows(int idConatinerInit, const ContainerNodeType & tipofin);
	FlowHeap getAvailableFlows(const ContainerNodeType & tipoIni, int idContainerFin);
	FlowHeap getAvailableFlows(int idInit, int idFin);

	void addUsedNode(int nodeId);
	void removeUsedNode(int nodeId);
	void addUsedEdge(int idSorce, int idTarget);
	void removeUsedEdge(int idSorce, int idTarget);

	inline bool existsContainer(int idContainer) {
		return (graph->getNode(idContainer) != NULL);
	}

	inline bool areConected(int idSource, int idTarget) {
		return (graph->areConnected(idSource, idTarget));
	}
	inline void saveGraph(const std::string & path) {
		graph->saveGraph(path);
	}

	//getters & setters
	inline Graph<ExecutableContainerNode, Edge>* getGraph() {
		return graph;
	}
	inline typename ExecutableContainerSubGraphPtr getSubgraphs() {
		return graph->getSubGraphs();
	}
	inline std::unordered_set<int>* getUsedNodes() {
		return usedNodes;
	}
protected:
	std::string name;
	Graph<ExecutableContainerNode, Edge>* graph;
	std::unordered_set<int>* usedNodes;
	std::unordered_set<std::pair<int, int>, PairIntIntHashFunction>* usedEges;

	void getAvailableFlows_recursive_type(int idSource, vector<int> & visitados,
		ExecutableContainerEdgeVector & recorridos,
		FlowHeap & flows,
		ExecutableContainerNodePtr actual,
		const ContainerNodeType & destinationType, bool reverse);
	void getAvailableFlows_recursive_id(int idSource, vector<int> & visitados,
		ExecutableContainerEdgeVector & recorridos,
		FlowHeap & flows,
		ExecutableContainerNodePtr actual, int idDestination);

	ExecutableContainerNodeVector getAllCompatibleNodes(const ContainerNodeType & type, const ExecutableContainerNodeVector & nodeList);
	ExecutableContainerEdgeVector getAvailableEdges(ExecutableContainerNodePtr actual, bool reversed);

	bool isNodeAvailable(ExecutableContainerNodePtr node);
	bool isNodeAvailable(int nodeId);

	bool isEdgeAvailable(ExecutableContainerEdgePtr edge);
	bool isEdgeAvailable(int idSource, int idTarget);

	ExecutableContainerEdgePtr makeEdge(int idSource, int idTarget);
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_EXECUTABLEMACHINEGRAPH_H_ */
