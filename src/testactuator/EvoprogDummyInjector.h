/*
 * EvoprogDummyInjector.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef TESTACTUATOR_EVOPROGDUMMYINJECTOR_H_
#define TESTACTUATOR_EVOPROGDUMMYINJECTOR_H_

#include "../fluidControl/executable/containers/actuators/liquids/Injector.h"
#include "../fluidControl/machineGraph/ContainerNodeType.h"
#include "../fluidControl/executable/containers/actuators/communications/CommunicationsInterface.h"

//cereal
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

class EvoprogDummyInjector: public Injector {
public:
	EvoprogDummyInjector() : Injector() {
	}
	EvoprogDummyInjector(int communications);
	virtual ~EvoprogDummyInjector();

	virtual void injectLiquid(double rate);
	virtual std::string getInstructions();
	virtual int getMovementType();

	//SERIALIZATIoN
	template<class Archive>
	void serialize(Archive & ar, std::uint32_t const version);
};

template<class Archive>
inline void EvoprogDummyInjector::serialize(Archive& ar,
		const std::uint32_t version) {
	if (version <= 1) {
		Injector::serialize(ar, version);
	}
}

// Associate some type with a version number
CEREAL_CLASS_VERSION( EvoprogDummyInjector, 1 );

// Include any archives you plan on using with your type before you register it
// Note that this could be done in any other location so long as it was prior
// to this file being included
#include <cereal/archives/json.hpp>
// Register DerivedClass
CEREAL_REGISTER_TYPE_WITH_NAME(EvoprogDummyInjector, "EvoprogDummyInjector");

#endif /* TESTACTUATOR_EVOPROGDUMMYINJECTOR_H_ */
