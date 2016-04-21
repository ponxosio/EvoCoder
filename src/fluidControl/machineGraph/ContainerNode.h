/*
 * ContainerNode.h
 *
 *  Created on: 8 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_MACHINEGRAPH_CONTAINERNODE_H_
#define SRC_FLUIDCONTROL_MACHINEGRAPH_CONTAINERNODE_H_

#include <string>
#include  <stdexcept>
#include <iostream>

//boost
#include <boost/algorithm/string/trim.hpp>

#include "../../../lib/easylogging++.h"
//local
#include "../../util/Patch.h"
#include "../../util/Utils.h"
#include "../../graph/Node.h"

//NAME CONSTANTS
#define CONT_FLOW_NAME  "CF"
#define CONT_INLET_NAME  "CI"
#define DISC_FLOW_NAME  "DF"
#define DISC_INLET_NAME  "DI"
#define CONV_SWITCH_NAME  "CS"
#define SINK_NAME  "SK"
#define DIV_SWITCH_NAME  "DS"
#define UNKNOW_NAME "UN"

//PATH CONSTANTS
#define CONT_FLOW_IMG "\\Img\\continuousflow.png"
#define CONT_INLET_IMG "\\Img\\continuousinlet.png"
#define DISC_FLOW_IMG "\\Img\\convergentswitch.png"
#define DISC_INLET_IMG "\\Img\\discreteflow.png"
#define CONV_SWITCH_IMG "\\Img\\discreteinlet.png"
#define SINK_IMG "\\Img\\sink.png"
#define DIV_SWITCH_IMG "\\Img\\divergentswitch.png"
#define UNKNOW_IMG "\\Img\\unknowContainer.png"

/*** Enum for the type of microfluidic elements ***/
typedef enum NodeType_ {
	continuous_flow_chamber,	// chamber with peristaltic pump or similar
	continuous_inlet,
	discrete_flow_chamber,	// chamber with syringe pump or similar
	discrete_inlet,
	sensor,			// sensor
	sink,			// pasive element
	convergent_switch,// convergent switch (chamber connected to a switch converging from various chambers)
	divergent_switch,// divergent switch (chamber connected to a switch diverging to various chambers)
	unknow // the type of this node is still unknow
} NodeType;

class ContainerNode: public Node {

public:
	//methods
	/**
	 * return the string value of the enum type
	 * @param type enum with the value to be returned as string
	 * @return the string corresponding to enum type.
	 */
	static std::string getTypeString(NodeType type);
	/**
	 * Return in type, the enum value corresponding to the typeString
	 * @param typeString string with the node type in text
	 * @param type where the value is returned
	 * @return true if the typeString is an existing type, false otherwise.
	 * if false is returned the value of type is not correct.
	 */
	static bool getStringType(std::string typeString, NodeType & type);
	/**
	 * Return the relative path of the file that contains the image of the passing type.
	 * @param type type of the image to return
	 * @return relative path of the file containing the image for the passing type.
	 */
	static std::string getTypeImagePath(NodeType type);

	//Obligatory constructors if is dereived from NODE
	ContainerNode();
	ContainerNode(const ContainerNode & node);
	//
	ContainerNode(int idConatiner, NodeType type, float capacity);

	virtual ~ContainerNode();

	//getters and setters
	inline NodeType getType() {
		return type;
	}
	inline void setType(NodeType type) {
		this->type = type;
	}

	inline float getVolume() {
		return volume;
	}
	inline void setVolume(float volume) {
		this->volume = volume;
	}

	inline float getCapacity() {
		return capacity;
	}
	inline void setCapacity(float capacity) {
		this->capacity = capacity;
	}

	//overriden virtual methods
	/**
	 * Returns a string with all the information of the node, must be with a format that loadNode can manage
	 *
	 * @return a string with all the necessary information to store this node
	 */
	virtual std::string toText();
	/**
	 * Loads all edge information, changing the object's internal attributes. throw invalid_argument if the line has
	 * an incorrect format.
	 *
	 * @param line text with the information of the edge, must be the compatible with the output of the above
	 * toText function
	 */
	virtual void loadNode(const std::string & line) throw (invalid_argument);
protected:
	/**
	 * Container type
	 */
	NodeType type;
	/**
	 * Maximum volume capacity of the container
	 */
	float capacity;
	/**
	 * Actual volume of the liquid in the container
	 */
	float volume;

	/**
	 * Parse a label line and extracts parameters
	 * @param label text with the label content
	 * @param type variable where the type is returned
	 * @param capacity variable where the capacity is returned
	 * @param errMessage variable where an error message is stored if any errors has occurred
	 * @return true if the process was successful , false if the label has format errors
	 */
	virtual bool processLabel (const std::string & label, NodeType & type, float & capacity, std::string & errMessage);
};

#endif /* SRC_FLUIDCONTROL_MACHINEGRAPH_CONTAINERNODE_H_ */
