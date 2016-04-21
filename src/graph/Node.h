/*
 * Node.h
 *
 *  Created on: 7 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_GRAPH_NODE_H_
#define SRC_GRAPH_NODE_H_

#include <string>
#include  <stdexcept>

//boost
#include <boost/algorithm/string/trim.hpp>

//local
#include "../util/Patch.h"

using namespace std;

/**
 * Minimum operations a all node must have, Base for all Node types to derive
 */
class Node {

public:
	//All derived clases must implement this two Constructor!!
	Node() {
		this->containerID = 0;
	}

	Node (const Node & node) {
		this->containerID = node.containerID;
	}
	//

	Node(int containerID) {
			this->containerID = containerID;
	}

	virtual ~Node(){}

	/**
	 * Returns the ID of this node
	 * @return Returns the ID of this node
	 */
	inline virtual int getContainerId() {
		return containerID;
	}

	/**
	 * Returns if this node is the same as n
	 * @param n the node to compare to
	 * @return true if the two nodes are the same, false otherwise
	 */
	inline virtual bool equals(const Node& n) {
		return (n.containerID == this->containerID);
	}

	/**
	 * Returns a string with all the information of the node, must be with a format that loadNode can manage
	 *
	 * @return a string with all the necessary information to store this node
	 */
	inline virtual string toText() {
		string vuelta = patch::to_string(containerID) + ";";
		return vuelta;
	}
	/**
	* Loads all edge information, changing the object's internal attributes. throw invalid_argument if the line has
	* an incorrect format.
	*
	* @param line text with the information of the edge, must be the compatible with the output of the above
	* toText function
	*/
	inline virtual void loadNode(const string & line)
			throw (invalid_argument) {
		string errMessage = "";
		size_t posEnd = line.find(";");

		if (posEnd != string::npos) {
			string  chunkId = line.substr(0, posEnd);
			boost::algorithm::trim(chunkId);

			int containerID;
			const char * c = chunkId.c_str();
			if (patch::stol(containerID, c)) {
				this->containerID = containerID;
			} else {
				errMessage = "Invalid syntax, \"" + chunkId
						+ "\" is not an integer number";
			}
		} else {
			errMessage = "Invalid syntax, \"" + line + "\" missing \';\'";
		}

		if (!errMessage.empty()) {
			throw(invalid_argument(errMessage));
		}
	}

	/**
	 * checks if this line has the format for a valid node, this method must changed depending of
	 * the format used for the node.
	 *
	 * @param line text that is going to be checked
	 * @return true if the format is for an edge, false otherwise
	 */
	inline virtual bool isNode(const string & line) {
		return (line.find("->") == string::npos);
	}

protected:
	int containerID;

};

#endif /* SRC_GRAPH_NODE_H_ */
