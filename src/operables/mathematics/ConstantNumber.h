/*
 * ConstantNumber.h
 *
 *  Created on: 15 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_OPERABLES_MATHEMATICS_CONSTANTNUMBER_H_
#define SRC_OPERABLES_MATHEMATICS_CONSTANTNUMBER_H_

//boost
#include <memory>

#include "../../util/Utils.h"
#include "../../util/Patch.h"
#include "MathematicOperable.h"

/**
 * Represents a constant number.
 */
class ConstantNumber: public MathematicOperable {
public:
	ConstantNumber(int value);
	ConstantNumber(double value);
	virtual ~ConstantNumber(){};

	virtual double getValue();
	virtual bool equal ( const MathematicOperable* obj ) const;

	inline virtual bool isPhysical() {return false;}

	inline virtual std::string toString() {
		return patch::to_string(value);
	}
protected:
	double value;
};

#endif /* SRC_OPERABLES_MATHEMATICS_CONSTANTNUMBER_H_ */
