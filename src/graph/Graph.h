/*
 * Graph.h
 *
 *  Created on: 7 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_GRAPH_GRAPH_H_
#define SRC_GRAPH_GRAPH_H_

//INCLUDES
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <stdexcept>
#include <cmath>

// file management
#include <iostream>
#include <sstream>
#include <fstream>

// data structures
#include <memory>
#include <vector>
#include <queue>
#include <utility>
#include <unordered_map>
#include <tuple>

// boost library
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <easylogging++.h>
//local
#include "../util/Patch.h"
#include "../util/Utils.h"
#include "Edge.h"
#include "Node.h"

//cereal
#include <cereal/cereal.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/vector.hpp>

//using namespace std;

/**
 *
 */
template <class NodeType, class EdgeType> class Graph {

	// Restrict this template for using only types derived from Node and edge Interfaces
	BOOST_STATIC_ASSERT((boost::is_base_of<Node, NodeType>::value));
	BOOST_STATIC_ASSERT((boost::is_base_of<Edge, EdgeType>::value));

public:
	Graph();
	virtual ~Graph();

	//insert graph
	bool addNode(shared_ptr<NodeType> node);
	bool addEdge(shared_ptr<EdgeType> edge);

	//retrieve
	shared_ptr<NodeType> getNode(int containerId) throw (std::invalid_argument);
	const vector<shared_ptr<EdgeType>> & getLeavingEdges(int idSource) throw (std::invalid_argument);
	const vector<shared_ptr<EdgeType>> & getArrivingEdges(int idSource) throw (std::invalid_argument);
	vector<shared_ptr<NodeType>> getAllNodes();
	bool areConnected(int idSource, int idTarget);

	//delete from graph
	bool removeNode(int nodeID);
	void removeEdge(const EdgeType & edge);
	void clear();

	//save graph
	bool saveGraph(const string& filename);

	//getters
	inline const vector<shared_ptr<EdgeType>> & getEdgeList() {
		return edgeList;
	}
	inline const vector<tuple<vector<shared_ptr<NodeType>>,vector<shared_ptr<EdgeType>>>> & getSubGraphs() {
		return subGraphs;
	}

	string toString();
protected:
	//attributes
	unordered_map<int, shared_ptr<NodeType>> nodeMap;
	unordered_map<int, vector<shared_ptr<EdgeType>>> leavingEdges;
	unordered_map<int, vector<shared_ptr<EdgeType>>> arrivingEdges;
	vector<tuple<vector<shared_ptr<NodeType>>,vector<shared_ptr<EdgeType>>>> subGraphs;
	vector<shared_ptr<EdgeType>> edgeList;

	//operations over graph
	void calculateSubgraphs();
};

template <class NodeType, class EdgeType>
Graph<NodeType,EdgeType>::Graph() {

}

template <class NodeType, class EdgeType>
Graph<NodeType,EdgeType>::~Graph() {}

/**
 * Deallocates all the nodes and edges, wipe out the containers without deallocating them.
 */
template<class NodeType, class EdgeType>
void Graph<NodeType, EdgeType>::clear() {
	edgeList->clear();
	nodeMap.clear();
	leavingEdges->clear();
	arrivingEdges->clear();
	subGraphs->clear();
}

/**
 * Adds a new node to the graph if not other  node exists with the same id
 *
 * @param node pointer to the node to add
 * @return true is the operation was successful, false otherwise
 */
template <class NodeType, class EdgeType>
bool Graph<NodeType,EdgeType>::addNode(shared_ptr<NodeType> node) {
	Node* nodeCast = dynamic_cast<Node*>(node.get());
	bool vuelta = false;
	if (nodeMap.find(nodeCast->getContainerId()) == nodeMap.end()) {
		nodeMap.insert(make_pair(nodeCast->getContainerId(), node));
		vector<shared_ptr<EdgeType>> edgesLeaving;
		vector<shared_ptr<EdgeType>> edgesArriving;
		leavingEdges.insert(make_pair(nodeCast->getContainerId(), edgesLeaving));
		arrivingEdges.insert(make_pair(nodeCast->getContainerId(), edgesArriving));
		vuelta = true;
	}
	return vuelta;
}

/**
 * Adds a new edge to the graph if the nodes that the edge connects does not exists and an equal(same attributes) edge
 * is not already in the graph
 *
 * @param edge pointer to edge to insert
 * @return true if successful, false otherwise
 */
template <class NodeType, class EdgeType>
bool Graph<NodeType,EdgeType>::addEdge(shared_ptr<EdgeType> edge) {
	Edge* edgeCast = dynamic_cast<Edge*>(edge.get());
	bool vuelta = false;

	auto nodeSource = nodeMap.find(edgeCast->getIdSource());
	// if the two node that the edge connects exits
	if ((nodeSource != nodeMap.end())
			&& (nodeMap.find(edgeCast->getIdTarget()) != nodeMap.end())) {
		edgeList.push_back(edge);
		leavingEdges.find(edgeCast->getIdSource())->second.push_back(edge);
		arrivingEdges.find(edgeCast->getIdTarget())->second.push_back(edge);
		vuelta = true;
	}
	return vuelta;
}

/**
 * Returns the node with the corresponding containerId
 *
 * @param containerId ID of the node
 * @return a pointer to the node if exists, NULL otherwise
 */
template <class NodeType, class EdgeType>
shared_ptr<NodeType> Graph<NodeType,EdgeType>::getNode(int containerId) throw (std::invalid_argument){
	auto nodeContainer = nodeMap.find(containerId);
	if (nodeContainer != nodeMap.end()) {
		return nodeContainer->second;
	} else {
		throw(std::invalid_argument("the node: " + patch::to_string(containerId) + " does not exists"));
	}
}

/**
 * Returns all the neighbors of the node with idSource
 *
 * @param idSource ID of the node to get the neighbors from
 * @return a pointer to a vector with all the edges pointing out the node with idSource if exists, NULL otherwise
 *
 */
template <class NodeType, class EdgeType>
const vector<shared_ptr<EdgeType>> & Graph<NodeType,EdgeType>::getLeavingEdges(int idSource) throw(std::invalid_argument) {

	auto it = leavingEdges.find(idSource);
	if (it != leavingEdges.end()) {
		return it->second;
	} else {
		throw(std::invalid_argument("the node: " + patch::to_string(idSource) + " does not exists"));
	}
}
template <class NodeType, class EdgeType>
vector<shared_ptr<NodeType>>  Graph<NodeType,EdgeType>::getAllNodes() {
	vector<shared_ptr<NodeType>> vuelta;

	for (auto it = nodeMap.begin();
				it != nodeMap.end(); ++it) {
		vuelta.push_back(it->second);
	}
	return vuelta;
}

/**
 * Removes and deallocates a node and all the edges connected to it from the graph. If the idNode exits.
 * @param idNode id of the node to remove
 * @return true if the idNode exists, false in other case.
 */
template <class NodeType, class EdgeType>
bool Graph<NodeType,EdgeType>::removeNode(int nodeID) {
	bool vuelta = false;

	auto nodeRemove = nodeMap.find(nodeID);
	if (nodeRemove != nodeMap.end()) {
		nodeMap.erase(nodeID);

		//remove all the edges that use idNode
		auto it = edgeList->begin();
		while (it != edgeList->end()) {
			Edge* actual = dynamic_cast<Edge*>((*it).get());
			if ((actual->getIdSource() == nodeID)
					|| (actual->getIdTarget() == nodeID)) {
				edgeList->erase(it);
			} else {
				++it;
			}
		}

		//remove neighbor from the list
		leavingEdges->erase(nodeID);
		arrivingEdges->erase(nodeID);

		vuelta = true;
	}
	return vuelta;
}

/**
 * Removes and deallocates all edges from the list that are equals as the passing one
 * @param edge object to be compared for removing from the vector
 */
template<class NodeType, class EdgeType>
void Graph<NodeType, EdgeType>::removeEdge(const EdgeType & edge) {
	auto it = edgeList->begin();
	while (it != edgeList->end()) {
		EdgeType* actual = (*it).get();
		if (actual->equals(edge)) {
			edgeList->erase(it);
		} else {
			++it;
		}
	}
}

/**
 * Save the graph as a text file compatible with GraphViz. with the passing filename.
 *
 * @param filename name of the file where the graph if saved
 * @return true if the operation was successful , false otherwise
 */
template <class NodeType, class EdgeType>
bool Graph<NodeType,EdgeType>::saveGraph(const string& filename) {
	bool error = false;
	ofstream myfile(filename.c_str());

	if (myfile.is_open()) {
		myfile << "digraph G {" << endl;

		// writing the nodes...
		for (auto it = nodeMap.begin();
				it != nodeMap.end(); ++it) {
			NodeType* actual = it->second.get();
			myfile << actual->toText()<< endl;
		}

		// writing the edges...
		for (auto it = edgeList.begin();
				it != edgeList.end(); ++it) {
			EdgeType* actual = (*it).get();
			myfile << actual->toText() << endl;
		}
		myfile << "}";
		myfile.close();
	} else {
		LOG(ERROR) << "Graph::saveGraph-> unable to open file: " + filename << endl;
		error = true;
	}
	return !error;
}

template<class NodeType, class EdgeType>
const vector<shared_ptr<EdgeType>> & Graph<NodeType, EdgeType>::getArrivingEdges(
		int idSource) throw (std::invalid_argument){

	auto it = arrivingEdges.find(idSource);
	if (it != arrivingEdges.end()) {
		return it->second;
	} else {
		throw(std::invalid_argument("the node: " + patch::to_string(idSource) + " does not exists"));
	}
}

/**
 * Search all disjoint subgraphs, the idea is to color connect nodes with the same color:
 *
 * for all edges->
 * 	*) if both connected nodes has no color: set the same random color to both;
 * 	*) if only one has a color: set the empty node's color so they be the same.
 * 	*) if both has one color and those colors are different: update all the nodes with
 * 		the bigger color to match the smaller one. (merge)
 */
template<class NodeType, class EdgeType>
void Graph<NodeType, EdgeType>::calculateSubgraphs() {
	unordered_map<int,int> node_colorMap;
	int lastColor = 0;

	for (auto it = edgeList.begin(); it != edgeList.end(); ++it) {
		Edge* actual = (*it).get();
		int idSource = actual->getIdSource();
		int idTarget = actual->getIdTarget();

		int colorSource =
				(node_colorMap.find(idSource) != node_colorMap.end()) ?
						node_colorMap.find(idSource)->second : -1;
		int colorTarget =
				(node_colorMap.find(idTarget) != node_colorMap.end()) ?
						node_colorMap.find(idTarget)->second : -1;

		if ((colorSource == -1) && (colorTarget == -1)) {
			node_colorMap.insert(make_pair(idTarget,lastColor));
			node_colorMap.insert(make_pair(idSource,lastColor));
			lastColor++;
		} else if ((colorSource != -1) && (colorTarget == -1)) {
			node_colorMap.insert(make_pair(idTarget,colorSource));
		} else if ((colorSource == -1) && (colorTarget != -1)) {
			node_colorMap.insert(make_pair(idSource,colorTarget));
		} else if ((colorSource != -1) && (colorTarget != -1)) {
			/* If the two has color a merge must be performed,
			 * the bigger color will be change to the smaller one
			 */
			if (colorSource != colorTarget) {
				int colorWin = min(colorSource, colorTarget);
				int colorChange =
						(colorWin == colorSource) ? colorTarget : colorSource;
				for (auto it = node_colorMap.begin(); it != node_colorMap.end();
						++it) {
					if (it->second == colorChange) {
						it->second = colorWin;
					}
				}
			}
		}
	}
	unordered_map<int,tuple<vector<shared_ptr<NodeType>>,vector<shared_ptr<EdgeType>>>> temp_color_nodeMap;
	for (auto it = node_colorMap.begin(); it != node_colorMap.end(); ++it) {
		int color = it->second;
		int idNode = it->first;

		auto nodeList = temp_color_nodeMap.find(color);
		if (nodeList == temp_color_nodeMap.end()) { //new color
			tuple<vector<shared_ptr<NodeType>>,vector<shared_ptr<EdgeType>>> newPair ( vector<shared_ptr<NodeType>>(), vector<shared_ptr<EdgeType>>());
			get<0>(newPair).push_back(getNode(idNode));
			get<1>(newPair).insert(get<1>(newPair).end(), getLeavingEdges(idNode).begin(), getLeavingEdges(idNode).end());

			temp_color_nodeMap.insert(make_pair(color, newPair));
		} else {
			tuple<vector<shared_ptr<NodeType>>,vector<shared_ptr<EdgeType>>> actualPair = nodeList->second;
			get<0>(actualPair).push_back(getNode(idNode));
			get<0>(actualPair).insert(get<1>(actualPair).end(), getLeavingEdges(idNode).begin(), getLeavingEdges(idNode).end());
		}
	}

	for (auto it = temp_color_nodeMap.begin(); it != temp_color_nodeMap.end(); ++it) {
		subGraphs->push_back(it->second);
	}
}

template<class NodeType, class EdgeType>
string Graph<NodeType, EdgeType>::toString() {
	ostringstream myfile;
	myfile << "digraph{";

	//print the nodes
	for (auto it = nodeMap.begin(); it != nodeMap.end(); ++it) {
		NodeType* actual = it->second.get();
		myfile << actual->toText();
	}

	//print the edges
	for (auto it = edgeList.begin();
			it != edgeList.end(); ++it) {
		EdgeType* actual = (*it).get();
		myfile << actual->toText();
	}

	myfile << "}";
	return myfile.str();
}

template<class NodeType, class EdgeType>
bool Graph<NodeType, EdgeType>::areConnected(int idSource, int idTarget) {
	bool vuelta = false;
	const vector<shared_ptr<Edge>> neighbors = getLeavingEdges(idSource);

	auto it = neighbors.begin();
	while (!vuelta && (it != neighbors.end())) {
		Edge* cast = (*it).get();
		vuelta = (cast->getIdTarget() == idTarget);
		++it;
	}
	return vuelta;
}

#endif /* SRC_GRAPH_GRAPH_H_ */
