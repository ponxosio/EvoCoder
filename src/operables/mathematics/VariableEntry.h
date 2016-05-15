/*
 * VariableEntry.h
 *
 *  Created on: 15 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_OPERABLES_MATHEMATICS_VARIABLEENTRY_H_
#define SRC_OPERABLES_MATHEMATICS_VARIABLEENTRY_H_

#include <string>

//boost
#include <boost/shared_ptr.hpp>

#include "../../protocolGraph/operations/container/ContainerOperation.h"
//local
#include "../../util/Utils.h"
#include "../VariableTable.h"
#include "MathematicOperable.h"

/**
 * Represents a variable stored in the VariableTable.
 */
class VariableEntry: public MathematicOperable {
public:
	VariableEntry(const std::string & name,
			boost::shared_ptr<VariableTable> sharedTable);
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
protected:
	/**
	 * name of the variable in the table
	 */
	std::string name;
	/**
	 * On delete does not deallocate this pointer to the variable table
	 */
	boost::shared_ptr<VariableTable> sharedTable;

};

#endif /* SRC_OPERABLES_MATHEMATICS_VARIABLEENTRY_H_ */
