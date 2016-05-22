/*
 * VariableEntry.cpp
 *
 *  Created on: 15 de mar. de 2016
 *      Author: angel
 */

#include "../mathematics/VariableEntry.h"

using namespace std;

VariableEntry::VariableEntry(const string & name, std::shared_ptr<VariableTable> sharedTable){
		this->name = name;
		this->sharedTable = sharedTable;
		/*
		 * if the variable is not at the table, must be
		 * inserted
		 */
		try {
			this->sharedTable.get()->getVaue(name);
		} catch (invalid_argument& e) {
			this->sharedTable.get()->setValue(name, 0.0);
		}
}

double VariableEntry::getValue() {
	return sharedTable.get()->getVaue(name);
}

bool VariableEntry::isPhysical() {
	return sharedTable.get()->getPhysical(name);
}

bool VariableEntry::equal(const MathematicOperable* obj) const{
	bool vuelta = false;
	if (Utils::IsType<VariableEntry, MathematicOperable>(obj)) {
		const VariableEntry* cast = dynamic_cast<const VariableEntry*>(obj);
		vuelta = (cast->name == this->name);
	}
	return vuelta;
}

void VariableEntry::setValue(double value) {
	sharedTable.get()->setValue(name, value);
}

void VariableEntry::setPhysical(bool physical) {
	sharedTable.get()->setPhysical(name, physical);
}
