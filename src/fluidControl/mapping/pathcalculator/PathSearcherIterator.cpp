#include "PathSearcherIterator.h"


PathSearcherIterator::PathSearcherIterator(std::shared_ptr<PathSearcher> engine)
{
	this->lastPosition = 0;
	this->engine = engine;
}

PathSearcherIterator::~PathSearcherIterator()
{
}

bool PathSearcherIterator::hasNext()
{
	bool has = true;
	if (lastPosition >= engine->getAvialableFlows()->size()) {
		LOG(DEBUG) << "Calculating next flow...";
		has = engine->calculateNextFlow();
	}
	return has;
}

bool PathSearcherIterator::hasNext(std::shared_ptr<std::unordered_set<int>> visitados)
{
	bool has = true;
	if (lastPosition >= engine->getAvialableFlows()->size()) {
		LOG(DEBUG) << "Calculating next flow...";
		has = engine->calculateNextFlow(visitados, 0);
	}
	return has;
}

std::shared_ptr<Flow<Edge>> PathSearcherIterator::next() throw (std::runtime_error)
{
	std::shared_ptr<Flow<Edge>> next;
	if (lastPosition < engine->getAvialableFlows()->size()) {
		next = engine->getAvialableFlows()->at(lastPosition);
	}
	else {
		LOG(DEBUG) << "Calculating next flow...";
		if (engine->calculateNextFlow()) {
			next = engine->getAvialableFlows()->at(lastPosition);
		}
		else {
			throw(std::runtime_error("iterator is already at the end"));
		}
	}
	lastPosition++;
	return next;
}

std::shared_ptr<Flow<Edge>> PathSearcherIterator::next(std::shared_ptr<std::unordered_set<int>> visitados) throw(std::runtime_error)
{
	std::shared_ptr<Flow<Edge>> next;
	if (lastPosition < engine->getAvialableFlows()->size()) {
		next = engine->getAvialableFlows()->at(lastPosition);
	}
	else {
		LOG(DEBUG) << "Calculating next flow...";
		if (engine->calculateNextFlow(visitados, 0)) {
			next = engine->getAvialableFlows()->at(lastPosition);
		}
		else {
			throw(std::runtime_error("iterator is already at the end"));
		}
	}
	lastPosition++;
	return next;
}

void PathSearcherIterator::begin()
{
	lastPosition = 0;
}

bool PathSearcherIterator::hasEnded()
{
	return engine->hasEnded();
}
