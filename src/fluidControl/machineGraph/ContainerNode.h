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
#include <boost/shared_ptr.hpp>

#include "../../../lib/easylogging++.h"
//local
#include "../../util/Patch.h"
#include "../../util/Utils.h"
#include "../../graph/Node.h"
#include "ContainerNodeType.h"

class ContainerNode: public Node {

public:
	//Obligatory constructors if is dereived from NODE
	ContainerNode();
	ContainerNode(const ContainerNode & node);
	//
	ContainerNode(int idConatiner, boost::shared_ptr<ContainerNodeType> type, float capacity);

	virtual ~ContainerNode();

	//ContainerType methods
	void changeContainerType(ContainerType type);
	void changeMovementType(MovementType type);
	void addAddon(AddOnsType type);
	void removeAddon(AddOnsType type);

	//getters and setters
	inline boost::shared_ptr<ContainerNodeType> getType() {
		return type;
	}
	inline void setType(boost::shared_ptr<ContainerNodeType> type) {
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
	boost::shared_ptr<ContainerNodeType> type;
	/**
	 * Maximum volume capacity of the container
	 */
	float capacity;
	/**
	 * Actual volume of the liquid in the container
	 */
	float volume;
};

#endif /* SRC_FLUIDCONTROL_MACHINEGRAPH_CONTAINERNODE_H_ */
