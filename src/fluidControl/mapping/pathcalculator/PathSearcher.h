#pragma once

#include <stack>
#include <unordered_set>
#include <vector>
#include <tuple>
#include <stdexcept>

#include "../../executable/ExecutableMachineGraph.h"

class PathSearcherIterator;
class PathManager;

class PathSearcher
{
public:
	PathSearcher(int idInicio, std::shared_ptr<ExecutableMachineGraph> machine, std::shared_ptr<PathManager> manager) throw (std::invalid_argument);
	virtual ~PathSearcher();

	std::shared_ptr<PathSearcherIterator> makeIterator();

	bool calculateNextFlow();
	bool calculateNextFlow(std::shared_ptr<std::unordered_set<int>> externalVisited, int LastStack);

	inline std::shared_ptr<std::vector<std::shared_ptr<Flow<Edge>>>> getAvialableFlows() {
		return calculatedFlows;
	}

	inline bool hasEnded() {
		return ended;
	}

protected:
	int idInicio;
	std::shared_ptr<ExecutableMachineGraph> machine;
	std::shared_ptr<PathManager> manager;

	//internal
	bool ended;
	std::shared_ptr<std::unordered_set<int>> visited;
	ExecutableMachineGraph::ExecutableContainerEdgeVector pending;
	std::shared_ptr<std::vector<std::shared_ptr<Flow<Edge>>>> calculatedFlows;
	std::shared_ptr<std::vector<std::tuple<std::shared_ptr<Edge>, std::shared_ptr<PathSearcherIterator>>>> executionStack;

	bool popNextEdge();
	bool popNextEdge(std::shared_ptr<std::unordered_set<int>> externalVisited, int lastSeen);
};

