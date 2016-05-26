/*
 * EvoprogMixer.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef TESTACTUATOR_EVOPROGMIXER_H_
#define TESTACTUATOR_EVOPROGMIXER_H_

#include <cmath>
#include <windows.h>

#include "../fluidControl/executable/containers/actuators/extras/Mixer.h"
#include "../util/Patch.h"
#include "../fluidControl/executable/containers/actuators/communications/CommunicationsInterface.h"

//cereal
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

class EvoprogMixer: public Mixer {
public:
	EvoprogMixer() : Mixer() {
		this->pinNumber = -1;
	}
	EvoprogMixer(int communications, int pinNumber);
	virtual ~EvoprogMixer();

	virtual std::string getInstructions();
	virtual void mix(double intensity);

	//SERIALIZATIoN
	template<class Archive>
	void serialize(Archive & ar, std::uint32_t const version);
protected:
	int pinNumber;
};

template<class Archive>
inline void EvoprogMixer::serialize(Archive& ar, const std::uint32_t version) {
	if (version <= 1) {
		Mixer::serialize(ar, version);
		ar(CEREAL_NVP(pinNumber));
	}
}

// Associate some type with a version number
CEREAL_CLASS_VERSION( EvoprogMixer, (int)1 );

// Include any archives you plan on using with your type before you register it
// Note that this could be done in any other location so long as it was prior
// to this file being included
#include <cereal/archives/json.hpp>
// Register DerivedClass
CEREAL_REGISTER_TYPE_WITH_NAME(EvoprogMixer, "EvoprogMixer");

#endif /* TESTACTUATOR_EVOPROGMIXER_H_ */
