#pragma once

#include <memory>
#include <unordered_set>
#include <stdexcept>

#include <easylogging++.h>

#include "PathSearcher.h"

class PathSearcherIterator
{
public:
	PathSearcherIterator(std::shared_ptr<PathSearcher> engine);
	virtual ~PathSearcherIterator();

	bool hasNext();
	bool hasNext(std::unordered_set<int> visitados);

	std::shared_ptr<Flow<Edge>> next() throw (std::runtime_error);
	std::shared_ptr<Flow<Edge>> next(std::unordered_set<int> visitados) throw (std::runtime_error);
	
	void begin();
	bool hasEnded();
	int getIdStart();

protected:
	int lastPosition;
	std::shared_ptr<PathSearcher> engine;
};

