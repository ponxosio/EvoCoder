/*
 * ConditionVariable.h
 *
 *  Created on: 15 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_OPERABLES_MATHEMATICS_MATHEMATICOPERABLE_H_
#define SRC_OPERABLES_MATHEMATICS_MATHEMATICOPERABLE_H_

#include <boost/shared_ptr.hpp>

/**
 * Interface that represents a variable in a comparison operation:
 */
class MathematicOperable {
public:
	MathematicOperable(){}
	virtual ~MathematicOperable(){}

	/**
	 * Returns the numeric value of the variable
	 * @return the numeric value of the variable
	 */
	virtual double getValue() = 0;
	/**
	 * Check if the variable stores physical values
	 * @return true if the variable stores physical values, false otherwise
	 */
	virtual bool isPhysical() = 0;
	/**
	 * Compares two Objects implementing this interface
	 * @param obj other object to be compared to
	 * @return true if both are the same, false otherwise.
	 */
	virtual bool equal ( const MathematicOperable* obj ) const = 0;

	virtual std::string toString() = 0;
};

#endif /* SRC_OPERABLES_MATHEMATICS_MATHEMATICOPERABLE_H_ */
