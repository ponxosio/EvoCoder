/*
 * EvoprogLight.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef TESTACTUATOR_EVOPROGLIGHT_H_
#define TESTACTUATOR_EVOPROGLIGHT_H_

#include <windows.h>
#include <cmath>

#include "../util/Patch.h"
#include "../fluidControl/executable/containers/actuators/extras/Light.h"
#include "../fluidControl/executable/containers/actuators/communications/CommunicationsInterface.h"

//cereal
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

class EvoprogLight: public Light {
public:
	EvoprogLight(): Light() {
		this->pinIntensity = -1;
		this->pinWaveLength = -1;
	}
	EvoprogLight(int communications, int pinWaveLength, int pinIntensity);
	virtual ~EvoprogLight();

	virtual std::string getInstructions();
	virtual void applyLight(double waveLength, double intensity);

	//SERIALIZATIoN
	template<class Archive>
	void serialize(Archive & ar, std::uint32_t const version);
protected:
	int pinWaveLength;
	int pinIntensity;
};

template<class Archive>
inline void EvoprogLight::serialize(Archive& ar, const std::uint32_t version) {
	if (version <= 1) {
		Light::serialize(ar, version);
		ar(CEREAL_NVP(pinWaveLength), CEREAL_NVP(pinIntensity));
	}
}

// Associate some type with a version number
CEREAL_CLASS_VERSION( EvoprogLight, (int)1 );

// Include any archives you plan on using with your type before you register it
// Note that this could be done in any other location so long as it was prior
// to this file being included
#include <cereal/archives/json.hpp>
// Register DerivedClass
CEREAL_REGISTER_TYPE_WITH_NAME(EvoprogLight, "EvoprogLight");

#endif /* TESTACTUATOR_EVOPROGLIGHT_H_ */
