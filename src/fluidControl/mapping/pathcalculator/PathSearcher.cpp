#include "PathSearcher.h"
#include "PathManager.h"
#include "PathSearcherIterator.h"

using namespace std;

PathSearcher::PathSearcher(int idInicio, std::shared_ptr<ExecutableMachineGraph> machine, PathManager* manager) throw (std::invalid_argument)
{
	this->idInicio = idInicio;
	this->machine = machine;
	this->manager = manager;
	this->ended = false;

	try {
		ExecutableMachineGraph::ExecutableContainerNodePtr start = machine->getContainer(idInicio);
		this->pending = machine->getAvailableEdges(start, false);
		this->calculatedFlows = make_shared<std::vector<std::shared_ptr<Flow<Edge>>>>();
		this->executionStack = make_shared<std::vector<std::tuple<std::shared_ptr<Edge>, std::shared_ptr<PathSearcherIterator>>>>();

		this->visited.insert(idInicio);
	}
	catch (std::invalid_argument & e) {
		throw(std::invalid_argument("PathSearcher(), exception occured; " + std::string(e.what())));
	}
}

PathSearcher::~PathSearcher()
{
}

bool PathSearcher::calculateNextFlow()
{
	bool finded = false;
	if (!ended) {
		if (executionStack->empty()) {
			if (!pending.empty()) {
				finded = popNextEdge();
			}
			else {
				ended = true;
			}
		}
		else {
			shared_ptr<PathSearcherIterator> topIt = get<1>(executionStack->back());
			shared_ptr<Edge> edge = get<0>(executionStack->back());
			if (topIt->hasNext(visited)) {
				std::shared_ptr<Flow<Edge>> next = topIt->next(visited);
				std::shared_ptr<Flow<Edge>> newFlow = make_shared<Flow<Edge>>(*(next.get()));
				newFlow->setIdStart(idInicio);
				newFlow->prepend(edge);

				calculatedFlows->push_back(newFlow);
				finded = true;
			}
			else {
				executionStack->pop_back();
				finded = calculateNextFlow();
			}
		}
	}
	return finded;
}

bool PathSearcher::calculateNextFlow(std::unordered_set<int> externalVisited, int lastStack)
{
	bool finded = false;
	for (auto it = visited.begin(); it != visited.end(); ++it) {
		externalVisited.insert(*it);
	}

	if (!ended) {
		if (executionStack->empty())
		{
			if (!pending.empty()) {
				finded = popNextEdge();
			}
			else {
				ended = true;
			}
		}
		else if (lastStack >= executionStack->size())
		{
			finded = popNextEdge(externalVisited, 0);
		}
		else
		{
			int idNextStack = (executionStack->size() - 1) - lastStack;
			shared_ptr<PathSearcherIterator> topIt = get<1>(executionStack->at(idNextStack));
			shared_ptr<Edge> edge = get<0>(executionStack->at(idNextStack));

			if (topIt->hasNext(externalVisited)) {
				std::shared_ptr<Flow<Edge>> next = topIt->next(externalVisited);
				std::shared_ptr<Flow<Edge>> newFlow = make_shared<Flow<Edge>>(*(next.get()));
				newFlow->setIdStart(idInicio);
				newFlow->prepend(edge);

				calculatedFlows->push_back(newFlow);
				finded = true;
			}
			else {
				if (topIt->hasEnded()) {
					executionStack->pop_back();
				}
				else {
					lastStack++;
				}
				finded = calculateNextFlow(externalVisited, lastStack);
			}
		}
	}
	return finded;
}

bool PathSearcher::popNextEdge()
{
	bool finded = false;
	if (!ended) {
		if (!pending.empty()) {
			shared_ptr<Edge> nextEdge = pending.back();
			pending.pop_back();

			int nextId = nextEdge->getIdTarget();
			if (machine->isEdgeAvailable(nextEdge) &&
				machine->isNodeAvailable(nextId) &&
				visited.find(nextId) == visited.end())
			{
				vector<shared_ptr<Edge>> v;
				v.push_back(nextEdge);
				calculatedFlows->push_back(make_shared<Flow<Edge>>(idInicio, nextId, v));

				executionStack->push_back(make_tuple(nextEdge, manager->getPathSearcher(nextId)));
				finded = true;
			}
			else {
				finded = popNextEdge();
			}
		}
	}
	return finded;
}

bool PathSearcher::popNextEdge(std::unordered_set<int> externalVisited, int lastSeen)
{
	bool finded = false;
	if (!ended) {
		if (!pending.empty()) {
			if (lastSeen < pending.size()) {
				int idnextEdge = (pending.size() - 1) - lastSeen;
				shared_ptr<Edge> nextEdge = pending.at(idnextEdge);
				int nextId = nextEdge->getIdTarget();

				if (externalVisited.find(nextId) == externalVisited.end()) {
					pending.erase(pending.begin() + idnextEdge);
					if (machine->isEdgeAvailable(nextEdge) &&
						machine->isNodeAvailable(nextId) &&
						visited.find(nextId) == visited.end())
					{
						vector<shared_ptr<Edge>> v;
						v.push_back(nextEdge);
						calculatedFlows->push_back(make_shared<Flow<Edge>>(idInicio, nextId, v));

						executionStack->push_back(make_tuple(nextEdge, manager->getPathSearcher(nextId)));
						finded = true;
					}
					else {
						finded = popNextEdge(externalVisited, lastSeen);
					}
				}
				else {
					lastSeen++;
					finded = popNextEdge(externalVisited, lastSeen);
				}
			}
		}
	}
	return finded;
}
