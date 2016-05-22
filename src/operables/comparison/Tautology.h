/*
 * Tautology.h
 *
 *  Created on: 28 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_OPERABLES_COMPARISON_TAUTOLOGY_H_
#define SRC_OPERABLES_COMPARISON_TAUTOLOGY_H_

#include "ComparisonOperable.h"
#include "../../util/Utils.h"

class Tautology: public ComparisonOperable {
public:
	Tautology() {
		this->negation = false;
	}
	virtual ~Tautology() {
	}

	/**
	 * Check if the comparison is true o false
	 * @return true if the comparison is true, false otherwise
	 */
	inline virtual bool conditionMet() {
		return !negation;
	}
	/**
	 * Check if the comparison used physical values
	 * @return true if the comparison uses physical values, false otherwise
	 */
	inline virtual bool isPhysical() {
		return false;
	}
	/**
	 * Checks if two ComparisonOperable are the same
	 * @param obj other ComparisonOperable to be compared
	 * @return true if they are the same, false otherwise
	 */
	inline virtual bool equal(ComparisonOperable* obj) const {
		bool vuelta = false;
		if (Utils::IsType<Tautology, ComparisonOperable>(obj)) {
			vuelta = true;
		}
		return vuelta;
	}
	/**
	 * !(tautology)
	 */
	inline virtual void negate() {
		negation = !negation;
	}

	inline virtual std::string toString() {
		std::string neg = negation ? "!" : "";
		return neg + "true";
	}
protected:
	bool negation;
};

#endif /* SRC_OPERABLES_COMPARISON_TAUTOLOGY_H_ */
