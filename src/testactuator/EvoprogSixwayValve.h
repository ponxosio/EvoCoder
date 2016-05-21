/*
 * EvoprogSixwayValve.h
 *
 *  Created on: 11 de may. de 2016
 *      Author: angel
 */

#ifndef TESTACTUATOR_EVOPROGSIXWAYVALVE_H_
#define TESTACTUATOR_EVOPROGSIXWAYVALVE_H_

#include <windows.h>

#include <unordered_map>

#include "../fluidControl/executable/containers/actuators/liquids/Control.h"
#include "../util/Patch.h"
#include "../fluidControl/executable/containers/actuators/communications/CommunicationsInterface.h"

//cereal
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/unordered_map.hpp>


class EvoprogSixwayValve: public Control {
public:
	EvoprogSixwayValve() : Control() {
		this->valveNumber = -1;
		this->lastPos = 0;
	}
	EvoprogSixwayValve(int communications, int valveNumber);
	virtual ~EvoprogSixwayValve();

	virtual void addConnection(int idSource, int idTraget);
	virtual void setConnection(int idSource, int idTraget);
	virtual std::string getInstructions();

	//SERIALIZATIoN
	template<class Archive>
	void serialize(Archive & ar, std::uint32_t const version);
protected:
	int valveNumber;
	std::unordered_map<int, int> containerValveMap;
	int lastPos;

};

template<class Archive>
inline void EvoprogSixwayValve::serialize(Archive& ar,
		const std::uint32_t version) {
	if (version <= 1) {
		Control::serialize(ar, version);
		ar(CEREAL_NVP(valveNumber), CEREAL_NVP(containerValveMap), CEREAL_NVP(lastPos));
	}
}

// Associate some type with a version number
CEREAL_CLASS_VERSION( EvoprogSixwayValve, 1 );

// Include any archives you plan on using with your type before you register it
// Note that this could be done in any other location so long as it was prior
// to this file being included
#include <cereal/archives/json.hpp>
// Register DerivedClass
CEREAL_REGISTER_TYPE_WITH_NAME(EvoprogSixwayValve, "EvoprogSixwayValve");

#endif /* TESTACTUATOR_EVOPROGSIXWAYVALVE_H_ */
