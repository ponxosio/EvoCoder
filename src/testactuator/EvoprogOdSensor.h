/*
 * EvoprogOdSensor.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef TESTACTUATOR_EVOPROGODSENSOR_H_
#define TESTACTUATOR_EVOPROGODSENSOR_H_

#include <windows.h>

#include "../../lib/easylogging++.h"

#include "../fluidControl/executable/containers/actuators/extras/ODSensor.h"
#include "../util/Patch.h"
#include "../fluidControl/executable/containers/actuators/communications/CommunicationsInterface.h"

//cereal
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

class EvoprogOdSensor: public ODSensor {
public:
	EvoprogOdSensor() :
			ODSensor() {
		this->port = -1;
	}
	EvoprogOdSensor(int command, int port);
	virtual ~EvoprogOdSensor();

	virtual std::string getInstructions();
	virtual double readOd() throw (std::invalid_argument);

	//SERIALIZATIoN
	template<class Archive>
	void serialize(Archive & ar, std::uint32_t const version);
protected:
	int port;
};

template<class Archive>
inline void EvoprogOdSensor::serialize(Archive& ar,
		const std::uint32_t version) {
	if (version <= 1) {
		ODSensor::serialize(ar, version);
		ar(CEREAL_NVP(port));
	}
}

// Associate some type with a version number
CEREAL_CLASS_VERSION( EvoprogOdSensor, (int)1 );

// Include any archives you plan on using with your type before you register it
// Note that this could be done in any other location so long as it was prior
// to this file being included
#include <cereal/archives/json.hpp>
// Register DerivedClass
CEREAL_REGISTER_TYPE_WITH_NAME(EvoprogOdSensor, "EvoprogOdSensor");

#endif /* TESTACTUATOR_EVOPROGODSENSOR_H_ */
