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
#include <tr1/unordered_set>
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
	ExecutableMachineGraph(const std::string & name);
	virtual ~ExecutableMachineGraph();

	void addContainer(ExecutableContainerNode* node);
	ExecutableContainerNode* getContainer(int idConatiner);

	bool connectExecutableContainer(int idSource, int idTarget);

	void printMachine(const std::string & path);

	std::priority_queue<Flow<Edge>, vector<Flow<Edge>>, FlowPtrComparator<Edge>> getAvailableFlows(
			const ContainerNodeType & tipoIni,
			const ContainerNodeType & tipofin,
			const std::vector<ExecutableContainerNode*> & subgraph);
	std::priority_queue<Flow<Edge>, vector<Flow<Edge>>, FlowPtrComparator<Edge>> getAvailableFlows(
			int idConatinerInit, const ContainerNodeType & tipofin);
	std::priority_queue<Flow<Edge>, vector<Flow<Edge>>, FlowPtrComparator<Edge>> getAvailableFlows(
			const ContainerNodeType & tipoIni, int idContainerFin);
	std::priority_queue<Flow<Edge>, vector<Flow<Edge>>, FlowPtrComparator<Edge>> getAvailableFlows(
			int idInit, int idFin);

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
	inline std::vector<std::pair<vector<ExecutableContainerNode*>*,vector<Edge*>*>>* getSubgraphs() {
		return graph->getSubGraphs();
	}
	inline std::tr1::unordered_set<int>* getUsedNodes() {
		return usedNodes;
	}
protected:
	std::string name;
	Graph<ExecutableContainerNode, Edge>* graph;
	std::tr1::unordered_set<int>* usedNodes;
	std::tr1::unordered_set<std::pair<int,int>,PairIntIntHashFunction>* usedEges;

	void getAvailableFlows_recursive_type(int idSource, vector<int> & visitados,
			vector<Edge*> & recorridos,
			std::priority_queue<Flow<Edge>, vector<Flow<Edge>>,
					FlowPtrComparator<Edge> > & flows,
			ExecutableContainerNode* actual,
			const ContainerNodeType & destinationType, bool reverse);
	void getAvailableFlows_recursive_id(int idSource, vector<int> & visitados,
			vector<Edge*> & recorridos,
			std::priority_queue<Flow<Edge>, vector<Flow<Edge>>,
					FlowPtrComparator<Edge> > & flows,
			ExecutableContainerNode* actual, int idDestination);

	vector<ExecutableContainerNode*> getAllCompatibleNodes(const ContainerNodeType & type, const std::vector<ExecutableContainerNode*> & nodeList);
	vector<Edge*> getAvailableEdges(ExecutableContainerNode* actual, bool reversed);

	bool isNodeAvailable(ExecutableContainerNode* node);
	bool isNodeAvailable(int nodeId);

	bool isEdgeAvailable(Edge* edge);
	bool isEdgeAvailable(int idSource, int idTarget);

};

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_EXECUTABLEMACHINEGRAPH_H_ */
