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
		return it->second->makeIterator();
	} else {
		std::shared_ptr<PathSearcher> newSearcher = std::make_shared<PathSearcher>(idStart, machine, shared_ptr<PathManager>(this));
		
		searchersMap.insert(std::make_pair(idStart, newSearcher));

		return newSearcher->makeIterator();
	}
}

