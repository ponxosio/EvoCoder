/*
 * MappingEngine.cpp
 *
 *  Created on: 12 de may. de 2016
 *      Author: angel
 */

#include "MappingEngine.h"

MappingEngine::MappingEngine(MachineGraph* sketch,
		ExecutableMachineGraph* machine) {
	this->sketch = sketch;
	this->machine = machine;

	this->containersMap = new std::tr1::unordered_map<int,int>();
	this->numberSolutionsMap = new std::tr1::unordered_map<int,int>();
	this->edgeFlowMap = new std::tr1::unordered_map<std::pair<int,int>, Flow<Edge>*, PairIntIntHashFunction>();
}

MappingEngine::~MappingEngine() {
	delete containersMap;

	for (auto it = edgeFlowMap->begin(); it != edgeFlowMap->end(); ++it) {
		delete it->second;
	}
	delete edgeFlowMap;
}

/*bool MappingEngine::startMapping() {
	bool success = false;
	std::vector<SubGraphSketch> skecthSubgraphs = *sketch->getSubgraphs();
	std::vector<SubGraphMachine>* machineSubgraphs = machine->getSubgraphs();

	if (!skecthSubgraphs.empty() && !machineSubgraphs->empty()) {
		success = trySubgraph(skecthSubgraphs, machineSubgraphs);
	}
	return success;
}*/

bool MappingEngine::startMapping() {
	std::vector<std::shared_ptr<Edge>> sketchEdgeList(sketch->getGraph()->getEdgeList());
	const std::vector<std::shared_ptr<ExecutableContainerNode>> machineSubgraphs = machine->getGraph()->getAllNodes();

	return mapSubgraph(sketchEdgeList, machineSubgraphs);
}

bool MappingEngine::mapSubgraph(std::vector<shared_ptr<Edge>>& edges, const std::vector<std::shared_ptr<ExecutableContainerNode>> & machineNodes) {
	bool success = false;
	if (!edges.empty()) {
		std::shared_ptr<Edge> actual = edges.back();
		edges.pop_back();

		FlowsHeap heap = getAvailableFlows(actual, machineNodes);
		while (!success && !heap.empty()) {
			Flow<Edge> actualFlow = heap.top();
			heap.pop();
			addSolution(actual, actualFlow);
			success = mapSubgraph(edges, machineNodes);
			if (!success) {
				removeSolution(actual);
			}
		}
		if (!success) {
			edges.push_back(actual);
		}
	} else {
		success = true;
	}
	return success;
}

void MappingEngine::addSolution(std::shared_ptr<Edge> edge, const Flow<Edge> & flow) throw(std::invalid_argument){
	Flow<Edge>* ptrFlow = new Flow<Edge>(flow);
	edgeFlowMap->insert(make_pair(std::pair<int,int>(edge->getIdSource(), edge->getIdTarget()), ptrFlow));

	if (containersMap->find(edge->getIdSource()) == containersMap->end()) {
		containersMap->insert(make_pair(edge->getIdSource(), flow.getIdStart()));
		numberSolutionsMap->insert(make_pair(edge->getIdSource(), 1));
	} else {
		if (containersMap->find(edge->getIdSource())->second != flow.getIdStart()) {
			throw(std::invalid_argument("attending to map " +
					patch::to_string(edge->getIdSource()) +
					" with tow different values" +
					patch::to_string(flow.getIdStart()) + "," +
					patch::to_string(containersMap->find(edge->getIdSource())->second)));
		} else {
			numberSolutionsMap->find(edge->getIdSource())->second += 1;
		}
	}

	if (containersMap->find(edge->getIdTarget()) == containersMap->end()) {
			containersMap->insert(make_pair(edge->getIdTarget(), flow.getIdFinish()));
			numberSolutionsMap->insert(make_pair(edge->getIdTarget(), 1));
		} else {
			if (containersMap->find(edge->getIdTarget())->second != flow.getIdFinish()) {
				throw(std::invalid_argument("attending to map " +
						patch::to_string(edge->getIdTarget()) +
						" with tow different values" +
						patch::to_string(flow.getIdFinish()) + "," +
						patch::to_string(containersMap->find(edge->getIdTarget())->second)));
			} else {
				numberSolutionsMap->find(edge->getIdTarget())->second += 1;
			}
		}

	machine->addUsedEdge(edge->getIdSource(), edge->getIdTarget());
	setNodesUsed(flow);
}

void MappingEngine::removeSolution(std::shared_ptr<Edge> edge) {
	if (numberSolutionsMap->find(edge->getIdSource())->second == 1) {
		containersMap->erase(edge->getIdSource());
		numberSolutionsMap->erase(edge->getIdSource());
	} else {
		numberSolutionsMap->find(edge->getIdSource())->second-=1;
	}

	if (numberSolutionsMap->find(edge->getIdTarget())->second == 1) {
		containersMap->erase(edge->getIdTarget());
		numberSolutionsMap->erase(edge->getIdTarget());
	} else {
		numberSolutionsMap->find(edge->getIdTarget())->second-=1;
	}

	std::pair<int,int> flowsKey(edge->getIdSource(), edge->getIdTarget());
	Flow<Edge>* flow = edgeFlowMap->find(flowsKey)->second;

	unsetNodesUsed(*flow);
	machine->removeUsedEdge(edge->getIdSource(), edge->getIdTarget());

	delete flow;
	edgeFlowMap->erase(flowsKey);
}

/*bool MappingEngine::trySubgraph(std::vector<SubGraphSketch>& sketchSubgraphs,
	std::vector<SubGraphMachine>* machineSubgraphs) {

	bool success = false;
	if (!sketchSubgraphs.empty()) {
		SubGraphSketch actualSketch = sketchSubgraphs.back();
		sketchSubgraphs.pop_back();
		for (auto it = machineSubgraphs->begin(); !success && it != machineSubgraphs->end(); ++it) {
			SubGraphMachine actualMachine = *it;
			std::vector<ContainerNode*>* nodesSketch = actualSketch.first;
			std::vector<ExecutableContainerNode*>* nodesmachine = actualMachine.first;
			std::tr1::unordered_set<int>* usedNodes = machine->getUsedNodes();
			if (ContainersUtils::areSubgraphCompatible<ContainerNode,
					ExecutableContainerNode>(*nodesSketch, *nodesmachine,
					*usedNodes)) {
				std::vector<Edge*> edgesSketch = *actualSketch.second;
				if (mapSubgraph(edgesSketch,actualMachine.first)) {
					success = trySubgraph(sketchSubgraphs, machineSubgraphs);
				}
			}
		}
	} else {
		success = true;
	}
	return success;
}*/

Flow<Edge>* MappingEngine::getMappedEdge(Edge* skectchEdge) throw(std::invalid_argument) {
	auto it = edgeFlowMap->find(std::pair<int,int>(skectchEdge->getIdSource(), skectchEdge->getIdTarget()));
	if (it == edgeFlowMap->end()) {
		throw(std::invalid_argument(
				"the edge (" + patch::to_string(skectchEdge->getIdSource())
						+ "," + patch::to_string(skectchEdge->getIdTarget())
						+ ") has no mapped value"));
	}
	return it->second;
}

int MappingEngine::getMappedContainerId(int sketchContainerId) throw(std::invalid_argument) {
	auto it = containersMap->find(sketchContainerId);
	if (it == containersMap->end()) {
		throw(std::invalid_argument("the container " + patch::to_string(sketchContainerId) + " has no mapped value"));
	}
	return it->second;
}

void MappingEngine::setNodesUsed(const Flow<Edge>& flow) {
	std::vector<Edge*> edges = flow.getPaths();
	for(auto it = edges.begin(); it != edges.end(); ++it) {
		machine->addUsedNode((*it)->getIdSource());
		machine->addUsedNode((*it)->getIdTarget());
	}
}

void MappingEngine::unsetNodesUsed(const Flow<Edge>& flow) {
	std::vector<Edge*> edges = flow.getPaths();
	for (auto it = edges.begin(); it != edges.end(); ++it) {
		machine->removeUsedNode((*it)->getIdSource());
		machine->removeUsedNode((*it)->getIdTarget());
	}
}

FlowsHeap MappingEngine::getAvailableFlows(std::shared_ptr<Edge> actual,
		const std::vector<std::shared_ptr<ExecutableContainerNode>> & machineNodes) {

	if (!isMapped(actual->getIdSource()) && !isMapped(actual->getIdTarget())) {
		ContainerNodeType* typeSource = sketch->getContainer(
				actual->getIdSource())->getType().get();
		ContainerNodeType* typeTarget = sketch->getContainer(
				actual->getIdTarget())->getType().get();
		return machine->getAvailableFlows(*typeSource, *typeTarget,
				machineNodes);
	} else if (isMapped(actual->getIdSource())
			&& !isMapped(actual->getIdTarget())) {
		ContainerNodeType* typeTarget = sketch->getContainer(
						actual->getIdTarget())->getType().get();
		int idSourceMachine = containersMap->find(actual->getIdSource())->second;
		return machine->getAvailableFlows(idSourceMachine, *typeTarget);
	} else if (!isMapped(actual->getIdSource())
			&& isMapped(actual->getIdTarget())) {
		ContainerNodeType* typeSource = sketch->getContainer(
				actual->getIdSource())->getType().get();
		int idTargetMachine = containersMap->find(actual->getIdTarget())->second;
		return machine->getAvailableFlows(*typeSource, idTargetMachine);
	} else { //both mapped
		int idSourceMachine = containersMap->find(actual->getIdSource())->second;
		int idTargetMachine = containersMap->find(actual->getIdTarget())->second;
		return machine->getAvailableFlows(idSourceMachine, idTargetMachine);
	}
}
