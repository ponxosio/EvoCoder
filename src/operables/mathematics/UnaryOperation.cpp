/*
 * UnaryOperation.cpp
 *
 *  Created on: 4 de abr. de 2016
 *      Author: angel
 */

#include "UnaryOperation.h"

UnaryOperation::UnaryOperation(std::shared_ptr<MathematicOperable> variable,
		unaryOperations::UnaryOperator op) {
	this->variable = variable;
	this->op = op;
}

UnaryOperation::~UnaryOperation() {

}

double UnaryOperation::getValue() {
	MathematicOperable* value = variable.get();
	double vuelta = 0.0;

	switch(this->op) {
	case unaryOperations::absoluteValue:
		vuelta = fabs(value->getValue());
		break;
	}
	return vuelta;
}

bool UnaryOperation::isPhysical() {
	return (variable.get()->isPhysical());
}

bool UnaryOperation::equal(const MathematicOperable* obj) const {
	bool vuelta = false;
	if (Utils::IsType<UnaryOperation, MathematicOperable>(obj)) {
		const UnaryOperation* cast = dynamic_cast<const UnaryOperation*>(obj);
		vuelta = ((this->variable.get()->equal(cast->variable.get()))
				&& (this->op == cast->op));
	}
	return vuelta;
}

std::string UnaryOperation::getStringOp() {
	std::string vuelta;
	switch (this->op) {
	case unaryOperations::absoluteValue:
		vuelta = ABSOLUTE_VALUE_STRING;
		break;
	}
	return vuelta;
}
