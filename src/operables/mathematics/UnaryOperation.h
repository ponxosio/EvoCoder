/*
 * UnaryOperation.h
 *
 *  Created on: 4 de abr. de 2016
 *      Author: angel
 */

#ifndef SRC_OPERABLES_MATHEMATICS_UNARYOPERATION_H_
#define SRC_OPERABLES_MATHEMATICS_UNARYOPERATION_H_

#define ABSOLUTE_VALUE_STRING "fabs"

//boost
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <memory>

//local
#include "../../../lib/easylogging++.h"

#include "../../util/Utils.h"
#include "MathematicOperable.h"

namespace unaryOperations {
/*** Enum for the type of unary operator ***/
enum UnaryOperator {
	absoluteValue //abs()
};
}
class UnaryOperation: public MathematicOperable {
public:
	UnaryOperation(std::shared_ptr<MathematicOperable> variable,
			unaryOperations::UnaryOperator op);

	virtual ~UnaryOperation();

	/**
	 * Returns the numeric value of the variable
	 * @return the numeric value of the variable
	 */
	virtual double getValue();
	/**
	 * Check if the variable stores physical values
	 * @return true if the variable stores physical values, false otherwise
	 */
	virtual bool isPhysical();
	/**
	 * Compares two Objects implementing this interface
	 * @param obj other object to be compared to
	 * @return true if both are the same, false otherwise.
	 */
	virtual bool equal(const MathematicOperable* obj) const;

	inline virtual std::string toString() {
		return getStringOp() + "(" + variable.get()->toString() + ")";
	}

protected:
	std::shared_ptr<MathematicOperable> variable;
	unaryOperations::UnaryOperator op;

	std::string getStringOp();
	double dummy (double a);
};

#endif /* SRC_OPERABLES_MATHEMATICS_UNARYOPERATION_H_ */
