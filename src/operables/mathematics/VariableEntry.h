/*
 * VariableEntry.h
 *
 *  Created on: 15 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_OPERABLES_MATHEMATICS_VARIABLEENTRY_H_
#define SRC_OPERABLES_MATHEMATICS_VARIABLEENTRY_H_

#include <string>
#include <memory>

//cereal
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>

//local
#include "../../util/Utils.h"
#include "../VariableTable.h"
#include "MathematicOperable.h"

/**
 * Represents a variable stored in the VariableTable.
 */
class VariableEntry: public MathematicOperable {
public:
	VariableEntry();
	VariableEntry(const std::string & name,
			std::shared_ptr<VariableTable> sharedTable);
	/**
	 * Does not deallocates the sharedTable
	 */
	virtual ~VariableEntry() {
	}
	/**
	 * Returns the value from the variable table
	 * @return
	 */
	virtual double getValue();
	/**
	 * Check if the variable stores physical values
	 * @return true if the variable stores physical values, false otherwise
	 */
	virtual bool isPhysical();

	virtual bool equal(const MathematicOperable* obj) const;
	/**
	 * Sets the value of this variable at the variable table to the given value
	 * @param value
	 */
	void setValue(double value);
	/**
	 * Sets the physical flag of this variable at the variable table to the given value
	 * @param value
	 */
	void setPhysical(bool physical);

	inline virtual std::string toString() {
		return name;
	}

	//SERIALIZATIoN
	template<class Archive>
	void serialize(Archive & ar, std::uint32_t const version);
protected:
	/**
	 * name of the variable in the table
	 */
	std::string name;
	/**
	 * On delete does not deallocate this pointer to the variable table
	 */
	std::shared_ptr<VariableTable> sharedTable;

};

template<class Archive>
inline void VariableEntry::serialize(Archive& ar, const std::uint32_t version) {
	if (version == 1) {
		ar(CEREAL_NVP(name), CEREAL_NVP(sharedTable));
	}
}

// Associate some type with a version number
CEREAL_CLASS_VERSION( VariableEntry, 1 );

// Include any archives you plan on using with your type before you register it
// Note that this could be done in any other location so long as it was prior
// to this file being included
#include <cereal/archives/json.hpp>
// Register DerivedClass
CEREAL_REGISTER_TYPE_WITH_NAME(VariableEntry, "VariableEntry");

#endif /* SRC_OPERABLES_MATHEMATICS_VARIABLEENTRY_H_ */
