/*
 * AritmeticOperation.h
 *
 *  Created on: 21 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_OPERABLES_MATHEMATICS_ARITHMETICOPERATION_H_
#define SRC_OPERABLES_MATHEMATICS_ARITHMETICOPERATION_H_

//operators strings
#define PLUS_STRING "+"
#define MINUS_STRING "-"
#define MULTIPLY_STRING "*"
#define DIVIDE_STRING "/"


#include <functional>

//boost
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

//local
#include "MathematicOperable.h"
#include "../../util/Utils.h"

namespace arithmetic {
/*** Enum for the type of arithmetic operator ***/
enum ArithmeticOperator {
	plus, // +
	minus, // -
	multiply, // *
	divide, // /
};
}

/**
 * Class that represents an arithmetic operation between two MathematicVariable s, operator available are + - * \
 */
class ArithmeticOperation: public MathematicOperable {
public:
	ArithmeticOperation(boost::shared_ptr<MathematicOperable> left,
			arithmetic::ArithmeticOperator op,
			boost::shared_ptr<MathematicOperable> right);

	virtual ~ArithmeticOperation();

	/**
	 * Returns the numeric value of the variable, resulting from the mathematical operation
	 * @return the numeric value of the variable
	 */
	virtual double getValue();

	inline virtual bool isPhysical() {return (leftVariable.get()->isPhysical() || rightVariable.get()->isPhysical());}

	/**
	 * Compares two Objects implementing this interface
	 * @param obj other object to be compared to
	 * @return true if both are the same, false otherwise.
	 */
	virtual bool equal(const MathematicOperable* obj) const;

	inline virtual  std::string toString() {
		return leftVariable.get()->toString() + " " + getStringOp() + " " + rightVariable.get()->toString();
	}

protected:
	//METHODS
	/**
	 * Returns a function that implements the comparison op
	 * @param op the comparison operation
	 * @return a function that implements the desired comparison
	 */
	static boost::function<double(double, double)> getFunctionType(
			arithmetic::ArithmeticOperator op);

	//Attributes
	/**
	 * Variable on the left of the operation
	 */
	boost::shared_ptr<MathematicOperable> leftVariable;
	/**
	 * Variable on the right of the operation
	 */
	boost::shared_ptr<MathematicOperable> rightVariable;
	/**
	 * Operator between variables
	 */
	arithmetic::ArithmeticOperator op;

	std::string getStringOp();
};

#endif /* SRC_OPERABLES_MATHEMATICS_ARITHMETICOPERATION_H_ */
