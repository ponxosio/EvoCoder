/*
 * Flow.h
 *
 *  Created on: 6 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_GRAPH_FLOW_H_
#define SRC_GRAPH_FLOW_H_

#include <vector>

//local
#include "../util/Patch.h"
#include "Edge.h"

class Flow {
public:
	Flow(const Flow & flow);
	Flow(int idStar, int idFinish);
	Flow(int idStar, int idFinish, const std::vector<Edge*> & paths);
	virtual ~Flow();

	void prepend(Edge* edge);
	void append(Edge* edge);
	void removePath(Edge* edge);

	bool checkLoop();
	bool equals(const Flow & flow);

	inline std::string toText() {
		return patch::to_string(idStart) + "->" + patch::to_string(idFinish);
	}

	inline int getIdFinish() const {
		return idFinish;
	}

	inline int getIdStart() const {
		return idStart;
	}

	inline const std::vector<Edge*>& getPaths() const {
		return paths;
	}
protected:
	int idStart;
	int idFinish;
	std::vector<Edge*> paths;
};

#endif /* SRC_GRAPH_FLOW_H_ */
