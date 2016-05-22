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

// boost library
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include "../../lib/easylogging++.h"
//local
#include "../util/Patch.h"
#include "../util/Utils.h"
#include "Edge.h"
#include "Node.h"

/**
 *
 */
template <class NodeType, class EdgeType> class Graph {

	// Restrict this template for using only types derived from Node and edge Interfaces
	BOOST_STATIC_ASSERT((boost::is_base_of<Node, NodeType>::value));
	BOOST_STATIC_ASSERT((boost::is_base_of<Edge, EdgeType>::value));

public:
	static Graph<NodeType,EdgeType>* loadGraph(string filename);

	Graph();
	virtual ~Graph();

	//insert graph
	bool addNode(NodeType* node);
	bool addEdge(EdgeType* edge);

	//retrieve
	NodeType* getNode(int containerId);
	const vector<EdgeType*>* getLeavingEdges(int idSource);
	const vector<EdgeType*>* getArrivingEdges(int idSource);
	const vector<NodeType*> getAllNodes();
	bool areConnected(int idSource, int idTarget);

	//delete from graph
	bool removeNode(int nodeID);
	void removeEdge(const EdgeType & edge);
	void clear();

	//save graph
	bool saveGraph(const string& filename);

	//getters
	inline vector<EdgeType*>* getEdgeList() {
		return edgeList;
	}
	inline vector<std::pair<vector<NodeType*>*,vector<EdgeType*>*>>* getSubGraphs() {
		if (subGraphs == NULL) {
			calculateSubgraphs();
		}
		return subGraphs;
	}

	string toString();
protected:
	//attributes
	unordered_map<int, NodeType*>* nodeMap;
	unordered_map<int, vector<EdgeType*>* >* leavingEdges;
	unordered_map<int, vector<EdgeType*>* >* arrivingEdges;
	vector<std::pair<vector<NodeType*>*,vector<EdgeType*>*>>* subGraphs;
	vector<EdgeType*> *edgeList;

	//methods
	static bool processLine(const string& line, Graph* graph);
	//operations over graph
	void calculateSubgraphs();
};

template <class NodeType, class EdgeType>
Graph<NodeType,EdgeType>::Graph() {
	nodeMap = new unordered_map<int, NodeType*>();
	leavingEdges = new unordered_map<int, vector<EdgeType*>*>();
	arrivingEdges = new unordered_map<int, vector<EdgeType*>*>();
	subGraphs = NULL;
	edgeList = new vector<EdgeType*>();
}

template <class NodeType, class EdgeType>
Graph<NodeType,EdgeType>::~Graph() {
	clear();
	delete edgeList;
	delete nodeMap;
	delete leavingEdges;
	delete arrivingEdges;
	if (subGraphs != NULL) {
		delete subGraphs;
	}
}

/**
 * Deallocates all the nodes and edges, wipe out the containers without deallocating them.
 */
template <class NodeType, class EdgeType>
void Graph<NodeType,EdgeType>::clear() {
	// free the edges
	for (typename vector<EdgeType*>::iterator it = edgeList->begin(); it != edgeList->end();
			++it) {
		delete *it;
	}
	edgeList->clear();

	//free the nodes
	for (typename unordered_map<int, NodeType* >::iterator it = nodeMap->begin();
			it != nodeMap->end(); ++it) {
		delete it->second;
	}
	nodeMap->clear();

	//free the neighbor map
	for (typename unordered_map<int, vector<EdgeType*>*>::iterator it = leavingEdges->begin();
			it != leavingEdges->end(); ++it) {
		delete it->second;
	}
	leavingEdges->clear();
	for (typename unordered_map<int, vector<EdgeType*>*>::iterator it =
			arrivingEdges->begin(); it != arrivingEdges->end(); ++it) {
		delete it->second;
	}
	arrivingEdges->clear();

	if (subGraphs != NULL) {
		//free the neighbor map
		for (auto it =
				subGraphs->begin(); it != subGraphs->end(); ++it) {
			std::pair<vector<NodeType*>*,vector<EdgeType*>*> actual = *it;
			delete actual.second;
			delete actual.first;
		}
		subGraphs->clear();
	}
}

/**
 * Adds a new node to the graph if not other  node exists with the same id
 *
 * @param node pointer to the node to add
 * @return true is the operation was successful, false otherwise
 */
template <class NodeType, class EdgeType>
bool Graph<NodeType,EdgeType>::addNode(NodeType* node) {
	Node* nodeCast = dynamic_cast<Node*>(node);
	bool vuelta = false;
	if (nodeMap->find(nodeCast->getContainerId()) == nodeMap->end()) {
		nodeMap->insert(make_pair(nodeCast->getContainerId(), node));
		leavingEdges->insert(make_pair(nodeCast->getContainerId(), new vector<EdgeType*>()));
		arrivingEdges->insert(make_pair(nodeCast->getContainerId(), new vector<EdgeType*>()));
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
bool Graph<NodeType,EdgeType>::addEdge(EdgeType* edge) {
	Edge* edgeCast = dynamic_cast<Edge*>(edge);
	bool vuelta = false;

	typename unordered_map<int, NodeType*>::iterator nodeSource = nodeMap->find(edgeCast->getIdSource());
	// if the two node that the edge connects exits
	if ((nodeSource != nodeMap->end())
			&& (nodeMap->find(edgeCast->getIdTarget()) != nodeMap->end())) {
		edgeList->push_back(edge);
		vector<EdgeType*>* vectorLeaving = leavingEdges->find(edgeCast->getIdSource())->second;
		vectorLeaving->push_back(edge);
		vector<EdgeType*>* vectorArriving = arrivingEdges->find(edgeCast->getIdTarget())->second;
		vectorArriving->push_back(edge);
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
NodeType* Graph<NodeType,EdgeType>::getNode(int containerId) {
	NodeType* vuelta = NULL;

	typename unordered_map<int, NodeType*>::iterator nodeContainer = nodeMap->find(containerId);
	if (nodeContainer != nodeMap->end()) {
		vuelta = nodeContainer->second;
	}
	return vuelta;
}

/**
 * Returns all the neighbors of the node with idSource
 *
 * @param idSource ID of the node to get the neighbors from
 * @return a pointer to a vector with all the edges pointing out the node with idSource if exists, NULL otherwise
 *
 */
template <class NodeType, class EdgeType>
const vector<EdgeType*>* Graph<NodeType,EdgeType>::getLeavingEdges(int idSource) {
	vector<EdgeType*>* vuelta = NULL;

	typename unordered_map<int, vector<EdgeType*>*>::iterator it = leavingEdges->find(idSource);
	if (it != leavingEdges->end()) {
		vuelta = it->second;
	}
	return vuelta;
}
template <class NodeType, class EdgeType>
const vector<NodeType*> Graph<NodeType,EdgeType>::getAllNodes() {
	vector<NodeType*> vuelta;

	for (typename unordered_map<int, NodeType* >::iterator it = nodeMap->begin();
				it != nodeMap->end(); ++it) {
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

	typename unordered_map<int, NodeType*>::iterator nodeRemove = nodeMap->find(nodeID);
	if (nodeRemove != nodeMap->end()) {
		//removes the node
		delete nodeRemove->second;
		nodeMap->erase(nodeID);

		//remove all the edges that use idNode
		typename vector<EdgeType*>::iterator it = edgeList->begin();
		while (it != edgeList->end()) {
			Edge* actual = dynamic_cast<Edge*>(*it);
			if ((actual->getIdSource() == nodeID)
					|| (actual->getIdTarget() == nodeID)) {
				edgeList->erase(it);
				delete actual;
			} else {
				++it;
			}
		}

		//remove neighbor from the list
		delete leavingEdges->find(nodeID)->second;
		leavingEdges->erase(nodeID);

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
	typename vector<EdgeType*>::iterator it = edgeList->begin();
	while (it != edgeList->end()) {
		EdgeType* actual = *it;
		if (actual->equals(edge)) {
			edgeList->erase(it);
			delete actual;
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
		for (typename unordered_map<int, NodeType*>::iterator it = nodeMap->begin();
				it != nodeMap->end(); ++it) {
			NodeType* actual = it->second;
			myfile << actual->toText()<< endl;
		}

		// writing the edges...
		for (typename vector<EdgeType*>::iterator it = edgeList->begin();
				it != edgeList->end(); ++it) {
			EdgeType* actual = *it;
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

/**
 * Returns a new graph with the content of the file at filename if the file exists and
 * has the correct format, the same used by saveGraph.
 *
 * @param filename path to the file containing the graph
 * @return a new graph with the content of the file if the operation was successful,
 * the file exists and has the correct format, NULL otherwise.
 */
template <class NodeType, class EdgeType>
Graph<NodeType,EdgeType>* Graph<NodeType,EdgeType>::loadGraph(string filename) {
	Graph<NodeType,EdgeType>* vuelta = NULL;
	ifstream myfile;
	bool error = false;

	myfile.open(filename.c_str());
	if (myfile.is_open()) {
		vuelta = new Graph<NodeType,EdgeType>();
		while (!error && !myfile.eof()) {
			string line;
			getline(myfile, line);
			if ((!line.empty()) && (line.find("digraph") == string::npos)
					&& (line.find("}") == string::npos)) {
				error = Graph::processLine(line, vuelta);
			}
		}
		if (error) {
			delete vuelta;
			vuelta = NULL;
		}
		myfile.close();
	} else {
		LOG(ERROR) << "Graph::loadGraph-> unable to open file: " + filename << endl;
	}
	return vuelta;
}

template<class NodeType, class EdgeType>
const vector<EdgeType*>* Graph<NodeType, EdgeType>::getArrivingEdges(
		int idSource) {
	vector<EdgeType*>* vuelta = NULL;

	typename unordered_map<int, vector<EdgeType*>*>::iterator it =
			arrivingEdges->find(idSource);
	if (it != arrivingEdges->end()) {
		vuelta = it->second;
	}
	return vuelta;
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
	subGraphs = new vector<std::pair<vector<NodeType*>*,vector<EdgeType*>*>>();
	unordered_map<int,int> node_colorMap;
	int lastColor = 0;

	for (auto it = edgeList->begin(); it != edgeList->end(); ++it) {
		Edge* actual = *it;
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
	unordered_map<int,std::pair<vector<NodeType*>*,vector<EdgeType*>*>> temp_color_nodeMap;
	for (auto it = node_colorMap.begin(); it != node_colorMap.end(); ++it) {
		int color = it->second;
		int idNode = it->first;

		auto nodeList = temp_color_nodeMap.find(color);
		if (nodeList == temp_color_nodeMap.end()) { //new color
			std::pair<vector<NodeType*>*,vector<EdgeType*>*> newPair = make_pair(new vector<NodeType*>(), new vector<EdgeType*>());
			newPair.first->push_back(getNode(idNode));
			newPair.second->insert(newPair.second->end(), getLeavingEdges(idNode)->begin(), getLeavingEdges(idNode)->end());

			temp_color_nodeMap.insert(make_pair(color, newPair));
		} else {
			std::pair<vector<NodeType*>*,vector<EdgeType*>*> actualPair = nodeList->second;
			actualPair.first->push_back(getNode(idNode));
			actualPair.second->insert(actualPair.second->end(), getLeavingEdges(idNode)->begin(), getLeavingEdges(idNode)->end());
		}
	}

	for (auto it = temp_color_nodeMap.begin(); it != temp_color_nodeMap.end(); ++it) {
		subGraphs->push_back(it->second);
	}
}

/**
 * If possible allocates and adds a new edge/node from the text line
 *
 * @param line line from the file with the  node/edge data
 * @param graph pointer to graph where the edge/node is being inserted
 * @return true if no error occurred, no sintax error in the line or semantic error in the graph data.
 */
template <class NodeType, class EdgeType>
bool Graph<NodeType,EdgeType>::processLine(const string& line, Graph* graph) {
	bool error = false;
	EdgeType tempEdge;
	NodeType tempNode;

	if (tempEdge.isEdge(line)) { //is an edge
		try {
			tempEdge.loadEdge(line);
			EdgeType* newEdge = new EdgeType(tempEdge);
			if (!graph->addEdge(newEdge)) {
				error = true;
				delete newEdge;
				LOG(ERROR) << "Graph::processLine-> error processing line: \"" << line
						<< "\", error inserting edge. \"" << newEdge->toText()
						<< "\"";
			}

		} catch (invalid_argument & e) {
			error = true;
			LOG(ERROR) << "Graph::processLine-> error processing line: \"" << line
					<< "\", " << e.what();
		}
	} else if (tempNode.isNode(line)) { // is a node
		try {
			tempNode.loadNode(line);
			NodeType* newNode = new NodeType(tempNode);

			if (!graph->addNode(newNode)) {
				error = true;
				delete newNode;
				LOG(ERROR) << "Graph::processLine-> error processing line: \"" << line
						<< "\", error inserting node. \"" << newNode->toText()
						<< "\"";
			}
		} catch (invalid_argument & e) {
			error = true;
			LOG(ERROR) << "Graph::processLine-> error processing line: \"" << line
					<< "\", " << e.what();
		}
	} else {
		LOG(ERROR) << "Graph::processLine-> error processing line: \"" << line
			 << "\", unknown format, not an edge not a node.";
	}
	return error;
}

template<class NodeType, class EdgeType>
string Graph<NodeType, EdgeType>::toString() {
	ostringstream myfile;
	myfile << "digraph{";

	//print the nodes
	for (typename unordered_map<int, NodeType*>::iterator it =
			nodeMap->begin(); it != nodeMap->end(); ++it) {
		NodeType* actual = it->second;
		myfile << actual->toText();
	}

	//print the edges
	for (typename vector<EdgeType*>::iterator it = edgeList->begin();
			it != edgeList->end(); ++it) {
		EdgeType* actual = *it;
		myfile << actual->toText();
	}

	myfile << "}";
	return myfile.str();
}

template<class NodeType, class EdgeType>
bool Graph<NodeType, EdgeType>::areConnected(int idSource, int idTarget) {
	bool vuelta = false;
	const vector<Edge*>* neighbors = getLeavingEdges(idSource);

	auto it = neighbors->begin();
	while (!vuelta && (it != neighbors->end())) {
		Edge* cast = *it;
		vuelta = (cast->getIdTarget() == idTarget);
		++it;
	}
	return vuelta;
}

#endif /* SRC_GRAPH_GRAPH_H_ */
