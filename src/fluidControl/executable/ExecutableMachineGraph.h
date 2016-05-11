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
#include <tr1/unordered_map>
#include <queue>

//local
#include "../../util/Patch.h"
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

	std::priority_queue<Flow<Edge>*, vector<Flow<Edge>*>,
			FlowPtrComparator<Edge>>* getAvailableFlows(
			const ContainerNodeType & tipoIni,
			const ContainerNodeType & tipofin);

	inline bool existsContainer(int idContainer) {
		return (graph->getNode(idContainer) != NULL);
	}

	inline bool areConected(int idSource, int idTarget) {
		return (graph->areConnected(idSource, idTarget));
	}
	inline void saveGraph(const std::string & path) {
		graph->saveGraph(path);
	}
	inline void addUsedNode(ExecutableContainerNode* node) {
		usedNodes->push_back(node);
	}
	void addUsedNode(int nodeId) throw(std::invalid_argument);
protected:
	std::string name;
	Graph<ExecutableContainerNode, Edge>* graph;
	std::vector<ExecutableContainerNode*>* usedNodes;

	vector<ExecutableContainerNode*> getAllCompatibleNodes(const ContainerNodeType & type);
	bool isNodeInVector(ExecutableContainerNode* node, const vector<int> & nodesIds);
	bool isNodeAvailable(ExecutableContainerNode* node);
	bool isNodeAvailable(int nodeId);

	void getAvailableFlows_recursive(int idSource, vector<int> & visitados, vector<Edge*> & recorridos,
			std::priority_queue<Flow<Edge>* , vector<Flow<Edge>*>,
					FlowPtrComparator<Edge> >* flows,
			ExecutableContainerNode* actual, const ContainerNodeType & destinationType);

};

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_EXECUTABLEMACHINEGRAPH_H_ */
