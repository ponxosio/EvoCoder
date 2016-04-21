/*
 * VariableTable.cpp
 *
 *  Created on: 15 de mar. de 2016
 *      Author: angel
 */

#include "VariableTable.h"

using namespace std;

VariableTable::VariableTable() {
	table = new tr1::unordered_map<string,  std::pair<double,bool>>();
}

VariableTable::~VariableTable() {
	table->clear();
	delete table;
}

double VariableTable::getVaue(const std::string& name)
		throw (std::invalid_argument) {

	double vuelta = 0.0d;
	auto entry = table->find(name);
	if (entry != table->end()) {
		vuelta = entry->second.first;
	} else {
		throw(invalid_argument("the key:\"" + name + "\" does not exits"));
	}
	return vuelta;
}

bool VariableTable::getPhysical(const std::string& name)
		throw (std::invalid_argument) {

	bool vuelta = false;
	auto entry = table->find(name);
	if (entry != table->end()) {
		vuelta = entry->second.second;
	} else {
		throw(invalid_argument("the key:\"" + name + "\" does not exits"));
	}
	return vuelta;
}

void VariableTable::setValue(const std::string& name, double value) {
	auto entry = table->find(name);
	if (entry != table->end()) {
		entry->second.first = value;
	} else {
		table->insert(make_pair(name, make_pair(value,false)));
	}
}

void VariableTable::setPhysical(const std::string& name, bool physical) {
	auto entry = table->find(name);
	if (entry != table->end()) {
		entry->second.second = physical;
	} else {
		table->insert(make_pair(name, make_pair(0.0, physical)));
	}
}

std::string VariableTable::serialize() {
	//TODO: implementar cuando se decida el formato
}

void VariableTable::deserialize() throw (std::invalid_argument) {
	//TODO: implementar cuando se decida el formato
}
