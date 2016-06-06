#include "PathManager.h"

PathManager::PathManager(std::shared_ptr<ExecutableMachineGraph> machine)
{
	this->machine = machine;
}

PathManager::~PathManager()
{
}

std::shared_ptr<PathSearcherIterator> PathManager::getPathSearcher(int idStart)
{
	auto it = searchersMap.find(idStart);
	if (it != searchersMap.end()) {
		std::shared_ptr<PathSearcher> searcher = it->second;
		return make_shared<PathSearcherIterator>(searcher);
	} else {
		std::shared_ptr<PathSearcher> newSearcher = std::make_shared<PathSearcher>(idStart, machine, this);
		
		searchersMap.insert(std::make_pair(idStart, newSearcher));

		return make_shared<PathSearcherIterator>(newSearcher);
	}
}

