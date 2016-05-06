/*
 * Flow.cpp
 *
 *  Created on: 6 de may. de 2016
 *      Author: angel
 */

#include "Flow.h"

Flow::Flow(const Flow& flow) {
	this->idStart = flow.idStart;
	this->idFinish = flow.idFinish;
	this->paths = std::vector<Edge*>();

	for (auto it = flow.paths.begin(); it != flow.paths.end(); ++it) {
		Edge* actual = *it;
		this->paths.push_back(actual);
	}
}

Flow::Flow(int idStar, int idFinish) {
	this->idStart = idStar;
	this->idFinish = idFinish;
	this->paths = std::vector<Edge*>();
}

Flow::Flow(int idStar, int idFinish, const std::vector<Edge*> & paths) {
	this->idStart = idStar;
	this->idFinish = idFinish;
	this->paths = std::vector<Edge*>();

	for (auto it = paths.begin(); it != paths.end(); ++it) {
		Edge* actual = *it;
		this->paths.push_back(actual);
	}
}

Flow::~Flow() {
}

void Flow::prepend(Edge* edge) {
	this->paths.insert(paths.begin(), edge);
}

void Flow::append(Edge* edge) {
	this->paths.push_back(edge);
}

void Flow::removePath(Edge* edge) {
	auto it = this->paths.begin();
	while (it != this->paths.end()) {
		Edge* actual = *it;
		if (actual->equals(*edge)) {
			this->paths.erase(it);
		} else {
			++it;
		}
	}
}

bool Flow::checkLoop() {
	bool loop = false;
	int idStart = paths.front()->getIdSource();
	auto it = paths.begin();

	while (!loop && it != paths.end()) {
		Edge* actual = *it;
		loop = (actual->getIdTarget() == idStart);
		++it;
	}
	return loop;
}

bool Flow::equals(const Flow& flow) {
	bool equals = ((flow.idStart == idStart) && (flow.idFinish == idFinish)
			&& (flow.paths.size() == paths.size()));

	auto itCompare = flow.paths.begin();
	for (auto itMe = paths.begin(); equals && itMe != paths.end(); ++itMe) {
		equals = (*itMe == *itCompare);
		 ++itCompare;
	}
	return equals;
}
