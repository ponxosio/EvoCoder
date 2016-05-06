/*
 * ExecutableContainerNode.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_EXECUTABLECONTAINERNODE_H_
#define SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_EXECUTABLECONTAINERNODE_H_

#include <string>
#include <stdexcept>

//boost
#include <boost/shared_ptr.hpp>

#include "actuatorsInterfaces/addOnsActuators/Mixer.h"
#include "actuatorsInterfaces/addOnsActuators/TemperatureAplicator.h"
#include "actuatorsInterfaces/addOnsActuators/LightAplicator.h"
#include "actuatorsInterfaces/addOnsActuators/ODSensor.h"
#include "../../machineGraph/ContainerNode.h"
#include "../../machineGraph/ContainerNodeType.h"

class ExecutableContainerNode: public ContainerNode {
public:
	//Obligatory methods if is derived from NODE
	ExecutableContainerNode() :
			ContainerNode() {
		this->od = boost::shared_ptr<ODSensor>();
		this->mix = boost::shared_ptr<Mixer>();
		this->light = boost::shared_ptr<LightAplicator>();
		this->temperature = boost::shared_ptr<TemperatureAplicator>();
	}
	ExecutableContainerNode(const ExecutableContainerNode & node) :
			ContainerNode(node) {
		this->od = node.od;
		this->mix = node.mix;
		this->light = node.light;
		this->temperature = node.temperature;
	}
	//

	ExecutableContainerNode(int idConatiner, boost::shared_ptr<ContainerNodeType> type, float capacity) :
			ContainerNode(idConatiner, type, capacity) {
		this->od = boost::shared_ptr<ODSensor>();
		this->mix = boost::shared_ptr<Mixer>();
		this->light = boost::shared_ptr<LightAplicator>();
		this->temperature = boost::shared_ptr<TemperatureAplicator>();
	}
	virtual ~ExecutableContainerNode(){}

	//getters & setters
	inline const boost::shared_ptr<LightAplicator>& getLight() const {
		return light;
	}

	inline void setLight(const boost::shared_ptr<LightAplicator>& light) {
		this->light = light;
	}

	inline const boost::shared_ptr<Mixer>& getMix() const {
		return mix;
	}

	inline void setMix(const boost::shared_ptr<Mixer>& mix) {
		this->mix = mix;
	}

	inline const boost::shared_ptr<ODSensor>& getOd() const {
		return od;
	}

	inline void setOd(const boost::shared_ptr<ODSensor>& od) {
		this->od = od;
	}

	inline const boost::shared_ptr<TemperatureAplicator>& getTemperature() const {
		return temperature;
	}

	inline void setTemperature(
			const boost::shared_ptr<TemperatureAplicator>& temperature) {
		this->temperature = temperature;
	}

	//virtual methods
	virtual void receiveLiquid(int source, int target, double rate) throw (std::invalid_argument) = 0;
	virtual void extractLiquid(int source, int target, double rate) throw (std::invalid_argument) = 0;
	virtual void connectContainer(int source, int target) = 0;

protected:
	boost::shared_ptr<ODSensor> od;
	boost::shared_ptr<Mixer> mix;
	boost::shared_ptr<LightAplicator> light;
	boost::shared_ptr<TemperatureAplicator> temperature;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLEMACHINEGRAPH_CONTAINERS_EXECUTABLECONTAINERNODE_H_ */
