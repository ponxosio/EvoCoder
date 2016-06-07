/*
 * FlowPtrComparator.h
 *
 *  Created on: 6 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_GRAPH_FLOWPTRCOMPARATOR_H_
#define SRC_GRAPH_FLOWPTRCOMPARATOR_H_

#include "Flow.h"

template<class EdgeType> class FlowPtrComparator {
public:
	virtual ~FlowPtrComparator(){}

	inline bool operator()(Flow<EdgeType>* f1, Flow<EdgeType>* f2) const {
		return (f1->getPaths().size() < f2->getPaths().size());
	}

	inline bool operator()(Flow<EdgeType> f1, Flow<EdgeType> f2) const {
		return (f1.getPaths().size() < f2.getPaths().size());
	}
};

#endif /* SRC_GRAPH_FLOWPTRCOMPARATOR_H_ */
