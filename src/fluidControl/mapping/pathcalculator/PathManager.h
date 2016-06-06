#pragma once

#include <unordered_map>
#include <memory>
#include <stdexcept>

#include "../../../util/Patch.h"
#include "../../executable/ExecutableMachineGraph.h"

#include "PathSearcher.h"
#include "PathSearcherIterator.h"

class PathManager
{
public:
	PathManager(std::shared_ptr<ExecutableMachineGraph> machine);
	virtual ~PathManager();

	std::shared_ptr<PathSearcherIterator> getPathSearcher(int idStart);

protected:
	std::unordered_map<int, std::shared_ptr<PathSearcher>> searchersMap;
	std::shared_ptr<ExecutableMachineGraph> machine;
};

