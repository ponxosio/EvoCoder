/*
 * ExecutableContainerNode.h
 *
 *  Created on: 3 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_EXECUTABLECONTAINERNODE_H_
#define SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_EXECUTABLECONTAINERNODE_H_

#include <string>
#include <stdexcept>

#include "../../machineGraph/ContainerNode.h"
#include "../../machineGraph/ContainerNodeType.h"
#include "actuators/extras/Light.h"
#include "actuators/extras/Mixer.h"
#include "actuators/extras/ODSensor.h"
#include "actuators/extras/Temperature.h"

class ExecutableContainerNode: public ContainerNode {
public:
	//Obligatory methods if is derived from NODE
	ExecutableContainerNode() :
			ContainerNode() {
		this->od = boost::shared_ptr<ODSensor>();
		this->mix = boost::shared_ptr<Mixer>();
		//this->light = NULL;
		//this->light = boost::shared_ptr<Light>();
		this->temperature = boost::shared_ptr<Temperature>();
	}
	ExecutableContainerNode(const ExecutableContainerNode & node) :
			ContainerNode(node) {
		this->od = node.od;
		this->mix = node.mix;
		//this->light = NULL;
		//this->light = node.light;
		this->temperature = node.temperature;
	}
	//

	ExecutableContainerNode(int idConatiner, boost::shared_ptr<ContainerNodeType> type, float capacity) :
			ContainerNode(idConatiner, type, capacity) {
		this->od = boost::shared_ptr<ODSensor>();
		this->mix = boost::shared_ptr<Mixer>();
		//this->light = NULL;
		//this->light = boost::shared_ptr<Light>();
		this->temperature = boost::shared_ptr<Temperature>();
	}
	virtual ~ExecutableContainerNode(){}

	//getters & setters
	inline const boost::shared_ptr<Light>& getLight() const {
		return light;
	}

	inline void setLight(const boost::shared_ptr<Light>& light) {
		addAddon(AddOnsType::light);
		this->light = light;
	}

	inline const boost::shared_ptr<Mixer>& getMix() const {
		return mix;
	}

	inline void setMix(const boost::shared_ptr<Mixer>& mix) {
		addAddon(AddOnsType::mixer);
		this->mix = mix;
	}

	inline const boost::shared_ptr<ODSensor>& getOd() const {
		return od;
	}

	inline void setOd(const boost::shared_ptr<ODSensor>& od) {
		addAddon(AddOnsType::OD_sensor);
		this->od = od;
	}

	inline const boost::shared_ptr<Temperature>& getTemperature() const {
		return temperature;
	}

	inline void setTemperature(
			const boost::shared_ptr<Temperature>& temperature) {
		addAddon(AddOnsType::temp);
		this->temperature = temperature;
	}

	//virtual methods
	virtual void setPositionInject(int source, int target) = 0;
	virtual void setPositionExtract(int source, int target) = 0;
	virtual void receiveLiquid(double rate) throw (std::invalid_argument)=0;
	virtual void extractLiquid(double rate) throw (std::invalid_argument)= 0;
	virtual void connectContainer(int source, int target) = 0;

protected:
	//Light* light;
	boost::shared_ptr<ODSensor> od;
	boost::shared_ptr<Mixer> mix;
	boost::shared_ptr<Light> light;
	boost::shared_ptr<Temperature> temperature;
};

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_EXECUTABLECONTAINERNODE_H_ */
