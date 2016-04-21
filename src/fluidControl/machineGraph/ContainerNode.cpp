/*
 * ContainerNode.cpp
 *
 *  Created on: 8 de mar. de 2016
 *      Author: angel
 */

#include "../machineGraph/ContainerNode.h"

using namespace std;

ContainerNode::ContainerNode(int idConatiner, NodeType type, float capacity) :
		Node(idConatiner) {
	this->type = type;
	this->capacity = capacity;
	this->volume = 0.0f;
}

ContainerNode::ContainerNode() :
		Node() {
	this->type = unknow;
	this->volume = 0.0f;
	this->capacity = 0.0f;
}

ContainerNode::ContainerNode(const ContainerNode& node) :
		Node(node) {
	this->type = node.type;
	this->capacity = node.capacity;
	this->volume = volume;
}

ContainerNode::~ContainerNode() {
	// TODO Auto-generated destructor stub
}

string ContainerNode::toText() {
	std::ostringstream stm;
	stm << patch::to_string(this->containerID) << " [image=\""
			<< Utils::getCurrentDir() << getTypeImagePath(this->type)
			<< "\", label=\"" << getTypeString(this->type) << " , "
			<< patch::to_string(this->capacity) << "\"];";
	return stm.str();
}

void ContainerNode::loadNode(const string& line) throw (invalid_argument) {
	string errMessage = "";

	size_t posOpen = line.find("[");
	size_t posClose = line.find("]");
	size_t posLbl = line.find("label=");

	if ((posOpen != string::npos) && (posClose != string::npos)
			&& (posLbl != string::npos)) {

		string chunkId = line.substr(0, posOpen);
		boost::algorithm::trim(chunkId);

		string chunkLbl = line.substr(posLbl + 7,
				(posClose - 1) - (posLbl + 7));
		boost::algorithm::trim(chunkLbl);

		NodeType type;
		float capacity;
		if (processLabel(chunkLbl, type, capacity, errMessage)) {
			int containerId;
			const char * c = chunkId.c_str();
			if (patch::stol(containerId, c)) {
				this->containerID = containerId;
				this->type = type;
				this->capacity = capacity;
				this->volume = 0.0f;
			} else {
				errMessage = "\" not an integer number:\"" + chunkId + "\"";
			}
		}
	} else {
		errMessage =
				" worng format, use \"nodeid [image=\"path\" , label=\"nodeTRype , capacity\"];\"";
	}

	if (!errMessage.empty()) {
		throw(invalid_argument(errMessage));
	}
}

bool ContainerNode::processLabel(const std::string & label, NodeType & type, float & capacity, string & errMessage) {
	bool vuelta = false;
	vector<string> tokens;
	Utils::tokenize(label, tokens, ",");

	if (tokens.size() == 2) {
		NodeType tempType;
		float tempCapacity = 0.0f;
		string typeStr = tokens[0];
		string capacityStr = tokens[1];

		boost::trim(typeStr);
		boost::trim(capacityStr);

		if (getStringType(typeStr, tempType)) {
			const char * c = capacityStr.c_str();
			if (patch::stod(tempCapacity, c)) {
				type = tempType;
				capacity = tempCapacity;
				vuelta = true;
			} else {
				errMessage = capacityStr + " is not a float number";
			}
		} else {
			errMessage = "unknown type: \"" + typeStr + "\".";
		}
	} else {
		errMessage = "wrong label:\"" + label + "\" use format \"nodeType, capacity\"";
	}
	return vuelta;
}

string ContainerNode::getTypeString(NodeType type) {
	string typeName;
	switch (type) {
	case discrete_flow_chamber:
		typeName = DISC_FLOW_NAME;
		break;
	case discrete_inlet:
		typeName = DISC_INLET_NAME;
		break;
	case continuous_flow_chamber:
		typeName = CONT_FLOW_NAME;
		break;
	case continuous_inlet:
		typeName = CONT_INLET_NAME;
		break;
	case sink:
		typeName = SINK_NAME;
		break;
	case divergent_switch:
		typeName = DIV_SWITCH_NAME;
		break;
	case convergent_switch:
		typeName = CONV_SWITCH_NAME;
		break;
	case unknow:
		typeName = UNKNOW_NAME;
		break;
	default:
		typeName = "";
		LOG(ERROR) << "Graph::getTypeString-> unknow nodeType: " << endl;
		break;
	}
	return typeName;
}

bool ContainerNode::getStringType(string typeString, NodeType & type) {
	bool error = false;
	if (typeString.compare(CONT_FLOW_NAME) == 0) {
		type = continuous_flow_chamber;
	} else if (typeString.compare(CONT_INLET_NAME) == 0) {
		type = continuous_inlet;
	} else if (typeString.compare(DISC_FLOW_NAME) == 0) {
		type = discrete_flow_chamber;
	} else if (typeString.compare(DISC_INLET_NAME) == 0) {
		type = discrete_inlet;
	} else if (typeString.compare(CONV_SWITCH_NAME) == 0) {
		type = convergent_switch;
	} else if (typeString.compare(DIV_SWITCH_NAME) == 0) {
		type = divergent_switch;
	} else if (typeString.compare(SINK_NAME) == 0) {
		type = sink;
	} else if (typeString.compare(UNKNOW_NAME) == 0) {
		type = unknow;
	} else {
		error = true;
	}
	return !error;
}

string ContainerNode::getTypeImagePath(NodeType type) {
	string imgPath;
	switch (type) {
	case discrete_flow_chamber:
		imgPath = DISC_FLOW_IMG;
		break;
	case discrete_inlet:
		imgPath = DISC_INLET_IMG;
		break;
	case continuous_flow_chamber:
		imgPath = CONT_FLOW_IMG;
		break;
	case continuous_inlet:
		imgPath = CONT_INLET_IMG;
		break;
	case sink:
		imgPath = SINK_IMG;
		break;
	case divergent_switch:
		imgPath = DIV_SWITCH_IMG;
		break;
	case convergent_switch:
		imgPath = CONV_SWITCH_IMG;
		break;
	case unknow:
		imgPath = UNKNOW_IMG;
		break;
	default:
		imgPath = "";
		LOG(ERROR) << "Graph::getTypeImagePath-> unknow nodeType: " + type << endl;
		break;
	}
	return imgPath;
}
