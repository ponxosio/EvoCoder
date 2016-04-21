/*
 * LogicalComparison.h
 *
 *  Created on: 22 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_OPERABLES_COMPARISON_BOOLEANCOMPARISON_H_
#define SRC_OPERABLES_COMPARISON_BOOLEANCOMPARISON_H_

//string operations
#define CONJUNCTION_STRING "&&"
#define DISJUNCTION_STRING "||"

//boost
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

//local
#include "ComparisonOperable.h"
#include "../../util/Utils.h"

namespace logical{
/*** Enum for the type of boolean operator ***/
enum BooleanOperator {
	conjunction, // and
	disjunction, // or 
};
}

/**
 * Class that represent a boolean operation between simple comparisons, for example: (t > 3) && (t < 5)
 */
class BooleanComparison: public ComparisonOperable {
public:
	BooleanComparison(bool negation,
			boost::shared_ptr<ComparisonOperable> left,
			logical::BooleanOperator op,
			boost::shared_ptr<ComparisonOperable> right);
	virtual ~BooleanComparison();

	/**
	 * Check if the comparison is true o false
	 * @return true if the comparison is true, false otherwise
	 */
	virtual bool conditionMet();
	/**
	 * Check if the comparison used physical values
	 * @return true if the comparison uses physical values, false otherwise
	 */
	inline virtual bool isPhysical() {
		return (left.get()->isPhysical() || right.get()->isPhysical());
	}
	/**
	 * Checks if two ComparisonOperable are the same
	 * @param obj other ComparisonOperable to be compared
	 * @return true if they are the same, false otherwise
	 */
	virtual bool equal(ComparisonOperable* obj) const;
	/**
	 * negates this comparison, not(comparison)
	 */
	inline virtual void negate() {negation = !negation;}

	inline virtual std::string toString() {
		std::string neg = negation ? "!" : "";
		return neg + left.get()->toString() + " " + getStringOp() + " " + right.get()->toString();
	}

protected:
	std::string getStringOp();
	/**
	 * Returns a function that implements the boolean operator op
	 * @param op the boolean operation
	 * @return a function that implements the desired operation
	 */
	boost::function<bool(bool, bool)> getFunctionType(
			logical::BooleanOperator op);

	//ATTRIBUTES
	boost::shared_ptr<ComparisonOperable> left;
	boost::shared_ptr<ComparisonOperable> right;
	logical::BooleanOperator op;
	bool negation;
};

#endif /* SRC_OPERABLES_COMPARISON_BOOLEANCOMPARISON_H_ */
