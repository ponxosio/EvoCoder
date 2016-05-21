/*
 * EvoprogTemperature.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef TESTACTUATOR_EVOPROGTEMPERATURE_H_
#define TESTACTUATOR_EVOPROGTEMPERATURE_H_

#include <windows.h>
#include <cmath>

#include "../util/Patch.h"
#include "../fluidControl/executable/containers/actuators/extras/Temperature.h"
#include "../fluidControl/executable/containers/actuators/communications/CommunicationsInterface.h"

//cereal
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

class EvoprogTemperature: public Temperature {
public:
	EvoprogTemperature() : Temperature() {
		this->pinNumber = -1;
	}
	EvoprogTemperature(int communications, int pinNumber);
	virtual ~EvoprogTemperature();

	virtual std::string getInstructions();
	virtual void apply(double degrees);

	//SERIALIZATIoN
	template<class Archive>
	void serialize(Archive & ar, std::uint32_t const version);
protected:
	int pinNumber;
};

template<class Archive>
inline void EvoprogTemperature::serialize(Archive& ar,
		const std::uint32_t version) {
	if (version <= 1) {
		Temperature::serialize(ar, version);
		ar(CEREAL_NVP(pinNumber));
	}
}

// Associate some type with a version number
CEREAL_CLASS_VERSION( EvoprogTemperature, 1 );

// Include any archives you plan on using with your type before you register it
// Note that this could be done in any other location so long as it was prior
// to this file being included
#include <cereal/archives/json.hpp>
// Register DerivedClass
CEREAL_REGISTER_TYPE_WITH_NAME(EvoprogTemperature, "EvoprogTemperature");

#endif /* TESTACTUATOR_EVOPROGTEMPERATURE_H_ */
