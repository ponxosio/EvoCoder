/*
 * Light.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_LIGHT_H_
#define SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_LIGHT_H_

#include "../Instructable.h"

//cereal
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

class Light: public Instructable {
public:
	Light() {
		this->communications = -1;
	}
	Light(int communications) :
			Instructable() {
		this->communications = communications;
	}
	virtual ~Light() {
	}

	virtual std::string getInstructions() = 0;
	virtual void applyLight(double waveLength, double intensity) = 0;

	//SERIALIZATIoN
	template<class Archive>
	void serialize(Archive & ar, std::uint32_t const version);
protected:
	int communications;
};

template<class Archive>
inline void Light::serialize(Archive& ar, const std::uint32_t version) {
	if (version <= 1) {
		ar(CEREAL_NVP(communications));
	}
}

// Associate some type with a version number
CEREAL_CLASS_VERSION( Light, 1 );

// Include any archives you plan on using with your type before you register it
// Note that this could be done in any other location so long as it was prior
// to this file being included
#include <cereal/archives/json.hpp>
// Register DerivedClass
CEREAL_REGISTER_TYPE_WITH_NAME(Light, "Light");

#endif /* SRC_FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_EXTRAS_LIGHT_H_ */
