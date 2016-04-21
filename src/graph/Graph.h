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

// file management
#include <iostream>
#include <sstream>
#include <fstream>

// data structures
#include <memory>
#include <vector>
#include <tr1/unordered_map>

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
	const vector<EdgeType*>* getNeighbors(int idSource);
	const vector<NodeType*> getAllNodes();

	//delete from graph
	bool removeNode(int nodeID);
	void removeEdge(const EdgeType & edge);
	void clear();

	//save graph
	bool saveGraph(const string& filename);

	//getters
	inline tr1::unordered_map<int, vector<EdgeType*> *>* getNeighborMap() const {
		return neighborMap;
	}

	string toString();
protected:
	//attributes
	tr1::unordered_map<int, NodeType*>* nodeMap;
	tr1::unordered_map<int, vector<EdgeType*>* >* neighborMap;
	vector<EdgeType*> *edgeList;

	//methods
	static bool processLine(const string& line, Graph* graph);
};

template <class NodeType, class EdgeType>
Graph<NodeType,EdgeType>::Graph() {
	nodeMap = new tr1::unordered_map<int, NodeType*>();
	neighborMap = new tr1::unordered_map<int, vector<EdgeType*>*>();
	edgeList = new vector<EdgeType*>();
}

template <class NodeType, class EdgeType>
Graph<NodeType,EdgeType>::~Graph() {
	clear();
	delete edgeList;
	delete nodeMap;
	delete neighborMap;
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
	for (typename tr1::unordered_map<int, NodeType* >::iterator it = nodeMap->begin();
			it != nodeMap->end(); ++it) {
		delete it->second;
	}
	nodeMap->clear();

	//free the nodes
	for (typename tr1::unordered_map<int, vector<EdgeType*>*>::iterator it = neighborMap->begin();
			it != neighborMap->end(); ++it) {
		delete it->second;
	}
	neighborMap->clear();
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
		neighborMap->insert(make_pair(nodeCast->getContainerId(), new vector<EdgeType*>()));
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

	typename tr1::unordered_map<int, NodeType*>::iterator nodeSource = nodeMap->find(edgeCast->getIdSource());
	// if the two node that the edge connects exits
	if ((nodeSource != nodeMap->end())
			&& (nodeMap->find(edgeCast->getIdTarget()) != nodeMap->end())) {
		edgeList->push_back(edge);
		vector<EdgeType*>* vector = neighborMap->find(edgeCast->getIdSource())->second;
		vector->push_back(edge);
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

	typename tr1::unordered_map<int, NodeType*>::iterator nodeContainer = nodeMap->find(containerId);
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
const vector<EdgeType*>* Graph<NodeType,EdgeType>::getNeighbors(int idSource) {
	vector<EdgeType*>* vuelta = NULL;

	typename tr1::unordered_map<int, vector<EdgeType*>*>::iterator it = neighborMap->find(idSource);
	if (it != neighborMap->end()) {
		vuelta = it->second;
	}
	return vuelta;
}
template <class NodeType, class EdgeType>
const vector<NodeType*> Graph<NodeType,EdgeType>::getAllNodes() {
	vector<NodeType*> vuelta;

	for (typename tr1::unordered_map<int, NodeType* >::iterator it = nodeMap->begin();
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

	typename tr1::unordered_map<int, NodeType*>::iterator nodeRemove = nodeMap->find(nodeID);
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
		delete neighborMap->find(nodeID)->second;
		neighborMap->erase(nodeID);

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
		for (typename tr1::unordered_map<int, NodeType*>::iterator it = nodeMap->begin();
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
	for (typename tr1::unordered_map<int, NodeType*>::iterator it =
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

#endif /* SRC_GRAPH_GRAPH_H_ */
