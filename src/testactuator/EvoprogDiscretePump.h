/*
 * EvoprogDiscretePump.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef TESTACTUATOR_EVOPROGDISCRETEPUMP_H_
#define TESTACTUATOR_EVOPROGDISCRETEPUMP_H_

#include "../fluidControl/executable/containers/actuators/liquids/Extractor.h"
#include "../fluidControl/machineGraph/ContainerNodeType.h"
#include "../fluidControl/executable/containers/actuators/communications/CommunicationsInterface.h"

//cereal
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

class EvoprogDiscretePump: public Extractor {
public:
	EvoprogDiscretePump() : Extractor() {
		this->pinNumber = -1;
	}
	EvoprogDiscretePump(int command, int pinNumber);
	virtual ~EvoprogDiscretePump();

	virtual void extractLiquid(double rate);
	virtual std::string getInstructions();
	virtual int getMovementType();

	//SERIALIZATIoN
	template<class Archive>
	void serialize(Archive & ar, std::uint32_t const version);
protected:
	int pinNumber;
};

template<class Archive>
inline void EvoprogDiscretePump::serialize(Archive& ar,
		const std::uint32_t version) {
	if (version <= 1) {
		Extractor::serialize(ar, version);
		ar(CEREAL_NVP(pinNumber));
	}
}

// Associate some type with a version number
CEREAL_CLASS_VERSION( EvoprogDiscretePump, (int)1 );

// Include any archives you plan on using with your type before you register it
// Note that this could be done in any other location so long as it was prior
// to this file being included
#include <cereal/archives/json.hpp>
// Register DerivedClass
CEREAL_REGISTER_TYPE_WITH_NAME(EvoprogDiscretePump, "EvoprogDiscretePump");

#endif /* TESTACTUATOR_EVOPROGDISCRETEPUMP_H_ */
