/*
 * Flow.h
 *
 *  Created on: 6 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_GRAPH_FLOW_H_
#define SRC_GRAPH_FLOW_H_

#include <vector>
#include <memory>

// boost library
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>

//local
#include "../util/Patch.h"
#include "Edge.h"

template<class EdgeType> class Flow {
	// Restrict this template for using only types derived from edge Interfaces
	BOOST_STATIC_ASSERT((boost::is_base_of<Edge, EdgeType>::value));

public:
	Flow(const Flow & flow);
	Flow(int idStar, int idFinish);
	Flow(int idStar, int idFinish, const std::vector<std::shared_ptr<EdgeType>> & paths);
	virtual ~Flow();

	void prepend(std::shared_ptr<EdgeType> edge);
	void append(std::shared_ptr<EdgeType> edge);
	void removePath(std::shared_ptr<EdgeType> edge);

	bool checkLoop();
	bool equals(const Flow & flow);

	std::string toText();

	inline int getIdFinish() const {
		return idFinish;
	}

	inline int getIdStart() const {
		return idStart;
	}

	inline const std::vector<std::shared_ptr<EdgeType>>& getPaths() const {
		return paths;
	}
protected:
	int idStart;
	int idFinish;
	std::vector<std::shared_ptr<EdgeType>> paths;
};

template<class EdgeType>
Flow<EdgeType>::Flow(const Flow& flow) {
	this->idStart = flow.idStart;
	this->idFinish = flow.idFinish;

	for (auto it = flow.paths.begin(); it != flow.paths.end(); ++it) {
		std::shared_ptr<EdgeType> actual = *it;
		this->paths.push_back(actual);
	}
}

template<class EdgeType>
Flow<EdgeType>::Flow(int idStar, int idFinish) {
	this->idStart = idStar;
	this->idFinish = idFinish;
}

template<class EdgeType>
Flow<EdgeType>::Flow(int idStar, int idFinish,
		const std::vector<std::shared_ptr<EdgeType>> & paths) {
	this->idStart = idStar;
	this->idFinish = idFinish;

	for (auto it = paths.begin(); it != paths.end(); ++it) {
		this->paths.push_back(*it);
	}
}

template<class EdgeType>
Flow<EdgeType>::~Flow() {
}
template<class EdgeType>
void Flow<EdgeType>::prepend(std::shared_ptr<EdgeType> edge) {
	this->paths.insert(paths.begin(), edge);
}

template<class EdgeType>
void Flow<EdgeType>::append(std::shared_ptr<EdgeType> edge) {
	this->paths.push_back(edge);
}

template<class EdgeType>
void Flow<EdgeType>::removePath(std::shared_ptr<EdgeType> edge) {
	auto it = this->paths.begin();
	while (it != this->paths.end()) {
		Edge* actual = *it;
		if (actual->equals(*(edge.get()))) {
			this->paths.erase(it);
		} else {
			++it;
		}
	}
}

template<class EdgeType>
bool Flow<EdgeType>::checkLoop() {
	bool loop = false;
	int idStart = paths.front()->getIdSource();
	auto it = paths.begin();

	while (!loop && it != paths.end()) {
		loop = ((*it)->getIdTarget() == idStart);
		++it;
	}
	return loop;
}

template<class EdgeType>
bool Flow<EdgeType>::equals(const Flow& flow) {
	bool equals = ((flow.idStart == idStart) && (flow.idFinish == idFinish)
			&& (flow.paths.size() == paths.size()));

	auto itCompare = flow.paths.begin();
	for (auto itMe = paths.begin(); equals && itMe != paths.end(); ++itMe) {
		equals = (*itMe == *itCompare);
		++itCompare;
	}
	return equals;
}

template<class EdgeType>
std::string Flow<EdgeType>::toText() {
	std::string text = patch::to_string(idStart) + "->"
			+ patch::to_string(idFinish) + ":";
	for (auto it = paths.begin(); it != paths.end(); ++it) {
		text += (*it)->toText();
	}
	return text;
}

#endif /* SRC_GRAPH_FLOW_H_ */
