/*
 * Mapping.cpp
 *
 *  Created on: 9 de mar. de 2016
 *      Author: angel
 */

#include "Mapping.h"

Mapping::Mapping(ExecutableMachineGraph* machine, const string & name) {
	this->machine = machine;
	this->sketch = new MachineGraph(name);
	this->operation = mapping::sketch;
}

Mapping::~Mapping() {
	delete sketch;
}

//OPERATIONS
bool Mapping::isSketching() {
	return (operation == mapping::sketch);
}

void Mapping::setSketching() {
	operation = mapping::sketch;
}

bool Mapping::isTest() {
	return (operation == mapping::test);
}

void Mapping::setTest() {
	operation = mapping::test;
}

bool Mapping::isExec_ep() {
	return (operation == mapping::exec_ep);
}

void Mapping::setExec_ep() {
	operation = mapping::exec_ep;
}

bool Mapping::isExec_general() {
	return (operation == mapping::exec_general);
}

void Mapping::setExec_general() {
	operation = mapping::exec_general;
}

//EXECUTIoN
void Mapping::setContinuosFlow(int idSource, int idTarget, double rate) {
	switch (operation) {
	case mapping::sketch:
		sketching_setContinuosFlow(idSource, idTarget, rate);
		break;
	case mapping::test:
		test_setContinuosFlow(idSource, idTarget, rate);
		break;
	case mapping::exec_general:
		exec_setContinuosFlow(idSource, idTarget, rate);
		break;
	case mapping::exec_ep:
		exec_setContinuosFlow(idSource, idTarget, rate);
		break;
	default:
		break;
	}
}

void Mapping::transfer(int idSource, int idTarget, double volume) {
	switch (operation) {
	case mapping::sketch:
		sketching_transfer(idSource, idTarget, volume);
		break;
	case mapping::test:
		test_transfer(idSource, idTarget, volume);
		break;
	case mapping::exec_general:
		exec_transfer(idSource, idTarget, volume);
		break;
	case mapping::exec_ep:
		exec_transfer(idSource, idTarget, volume);
		break;
	default:
		break;
	}
}

void Mapping::mix(int source1, int source2, int target, double volume1,
		double volume2) {

	switch (operation) {
	case mapping::sketch:
		sketching_mix(source1, source2, target, volume1, volume2);
		break;
	case mapping::test:
		test_mix(source1, source2, target, volume1, volume2);
		break;
	case mapping::exec_general:
		exec_mix(source1, source2, target, volume1, volume2);
		break;
	case mapping::exec_ep:
		exec_mix(source1, source2, target, volume1, volume2);
		break;
	default:
		break;
	}
}

void Mapping::applyLight(int id, double wavelength, double intensity) {
	switch (operation) {
	case mapping::sketch:
		sketching_applyLight(id, wavelength, intensity);
		break;
	case mapping::test:
		test_applyLight(id, wavelength, intensity);
		break;
	case mapping::exec_general:
		exec_applyLight(id, wavelength, intensity);
		break;
	case mapping::exec_ep:
		exec_applyLight(id, wavelength, intensity);
		break;
	default:
		break;
	}
}

void Mapping::applyTemperature(int id, double degrees) {
	switch (operation) {
	case mapping::sketch:
		sketching_applyTemperature(id, degrees);
		break;
	case mapping::test:
		test_applyTemperature(id, degrees);
		break;
	case mapping::exec_general:
		exec_applyTemperature(id, degrees);
		break;
	case mapping::exec_ep:
		exec_applyTemperature(id, degrees);
		break;
	default:
		break;
	}
}

void Mapping::stir(int id, double intensity) {
	switch (operation) {
	case mapping::sketch:
		sketching_stir(id);
		break;
	case mapping::test:
		test_stir(id, intensity);
		break;
	case mapping::exec_general:
		exec_stir(id, intensity);
		break;
	case mapping::exec_ep:
		exec_stir(id, intensity);
		break;
	default:
		break;
	}
}

double Mapping::getVolume(int id) {
	double vuelta = -1.0;

	switch (operation) {
	case mapping::sketch:
		break;
	case mapping::test:
		vuelta = test_getVolume(id);
		break;
	case mapping::exec_general:
		vuelta = exec_getVolume(id);
		break;
	case mapping::exec_ep:
		vuelta = exec_getVolume(id);
		break;
	default:
		break;
	}
	return vuelta;
}

double Mapping::measureOD(int id) {
	double vuelta = -1.0;

	switch (operation) {
	case mapping::sketch:
		sketching_measureOD(id);
		break;
	case mapping::test:
		vuelta = test_measureOD(id);
		break;
	case mapping::exec_general:
		vuelta = exec_measureOD(id);
		break;
	case mapping::exec_ep:
		vuelta = exec_measureOD(id);
		break;
	default:
		break;
	}
	return vuelta;
}

void Mapping::loadContainer(int containerID, double volume) {
	switch (operation) {
	case mapping::sketch:
		sketching_loadContainer(containerID, volume);
		break;
	case mapping::test:
		test_loadContainer(containerID, volume);
		break;
	case mapping::exec_general:
		exec_loadContainer(containerID, volume);
		break;
	case mapping::exec_ep:
		exec_loadContainer(containerID, volume);
		break;
	default:
		break;
	}
}

double Mapping::timeStept() {
	double vuelta = -1.0;

	switch (operation) {
	case mapping::sketch:
		vuelta = sketching_timeStep();
		break;
	case mapping::test:
		vuelta = test_timeStep();
		break;
	case mapping::exec_general:
		vuelta = exec_timeStep();
		break;
	case mapping::exec_ep:
		vuelta = exec_timeStep();
		break;
	default:
		break;
	}
	return vuelta;
}

//SKETCH
void Mapping::sketching_setContinuosFlow(int idSource, int idTarget,
		double rate) {

	LOG(DEBUG)<< "sketching setContinousFlow(" << patch::to_string(idSource) << ", "
	<< patch::to_string(idTarget) << ", " + patch::to_string(rate)
	<< ")";

	//Update source node
	if (sketch->existsContainer(idSource)) {
		ContainerNode* sourceNode = sketch->getContainer(idSource);
		if (sourceNode->getType().get()->isCompatibleMovement(MovementType::continuous)) {
			transformSourceContainer(idSource, idTarget, sourceNode, MovementType::continuous);
		} else {
			LOG(FATAL)<< "container: " << patch::to_string(idTarget) << " cannot be continuous because already is" << sourceNode->getType().get()->getMovementTypeString();
		}
	} else {
		sketch->addContainer(idSource, boost::shared_ptr<ContainerNodeType>(new ContainerNodeType(MovementType::continuous, ContainerType::inlet)), 0.0);
	}

	// Update target node
	if (sketch->existsContainer(idTarget)) {
		ContainerNode* targetNode = sketch->getContainer(idTarget);
		transformTargetContainer(idSource, idTarget, targetNode);
	} else {
		sketch->addContainer(idTarget, boost::shared_ptr<ContainerNodeType>(new ContainerNodeType(MovementType::irrelevant, ContainerType::sink)), 0.0);
	}
	/**** Connect source and target nodes ****/
	sketch->connectContainer(idSource, idTarget);
}

void Mapping::sketching_transfer(int idSource, int idTarget, double volume) {

	LOG(DEBUG)<< "sketching transfer(" << patch::to_string(idSource) << ", "
	<< patch::to_string(idTarget) << ", " << patch::to_string(volume)
	<< ")";

	//Update source node
	if (sketch->existsContainer(idSource)) {
		ContainerNode* sourceNode = sketch->getContainer(idSource);
		if (sourceNode->getType().get()->isCompatibleMovement(MovementType::discrete)) {
			transformSourceContainer(idSource, idTarget, sourceNode, MovementType::discrete);
		} else {
			LOG(FATAL)<< "container: " << patch::to_string(idTarget) << " cannot be discrete because already is" << sourceNode->getType().get()->getMovementTypeString();
		}
	} else {
		sketch->addContainer(idSource, boost::shared_ptr<ContainerNodeType>(new ContainerNodeType(MovementType::discrete, ContainerType::inlet)), 0.0);
	}

	// Update target node
	if (sketch->existsContainer(idTarget)) {
		ContainerNode* targetNode = sketch->getContainer(idTarget);
		transformTargetContainer(idSource, idTarget, targetNode);
	} else {
		sketch->addContainer(idTarget, boost::shared_ptr<ContainerNodeType>(new ContainerNodeType(MovementType::irrelevant, ContainerType::sink)), 0.0);
	}
	/**** Connect source and target nodes ****/
	sketch->connectContainer(idSource, idTarget);
}

void Mapping::transformSourceContainer(int idSource, int idTarget,
		ContainerNode* sourceNode, MovementType desiredType) {

	switch (sourceNode->getType().get()->getContainerType()) {
	case ContainerType::unknow:
		sketch->changeContainerType(idSource, ContainerType::inlet);
		sketch->changeMovementType(idSource, desiredType);
		break;
	case ContainerType::inlet:
		if (!sketch->areConected(idSource, idTarget)) {
			sketch->changeContainerType(idSource,
					ContainerType::divergent_switch);
		}
		break;
	case ContainerType::flow:
		if (!sketch->areConected(idSource, idTarget)) {
			sketch->changeContainerType(idSource,
					ContainerType::divergent_switch_sink);
		}
		break;
	case ContainerType::sink:
		sketch->changeContainerType(idSource, ContainerType::flow);
		sketch->changeMovementType(idSource, desiredType);
		break;
	case ContainerType::convergent_switch:
		sketch->changeContainerType(idSource,
				ContainerType::convergent_switch_inlet);
		sketch->changeMovementType(idSource, desiredType);
		break;
	case ContainerType::convergent_switch_inlet:
		if (!sketch->areConected(idSource, idTarget)) {
			sketch->changeContainerType(idSource,
					ContainerType::bidirectional_switch);
		}
		break;
	default:
		break;
	}
}

void Mapping::transformTargetContainer(int idSource, int idTarget,
		ContainerNode* targetNode) {

	switch(targetNode->getType().get()->getContainerType()) {
	case ContainerType::unknow:
		sketch->changeContainerType(idTarget, ContainerType::sink);
		break;
	case ContainerType::inlet:
		sketch->changeContainerType(idTarget, ContainerType::flow);
		break;
	case ContainerType::sink:
		if (!sketch->areConected(idSource, idTarget)) {
			sketch->changeContainerType(idTarget,
					ContainerType::convergent_switch);
		}
		break;
	case ContainerType::flow:
		if (!sketch->areConected(idSource, idTarget)) {
			sketch->changeContainerType(idTarget,
					ContainerType::convergent_switch_inlet);
		}
		break;
	case ContainerType::divergent_switch:
		sketch->changeContainerType(idTarget,
				ContainerType::divergent_switch_sink);
		break;
	case ContainerType::divergent_switch_sink:
		if (!sketch->areConected(idSource, idTarget)) {
			sketch->changeContainerType(idTarget,
					ContainerType::bidirectional_switch);
		}
		break;
	default:
		break;
	}
}

void Mapping::sketching_mix(int source1, int source2, int target,
		double volume1, double volume2) {

	LOG(DEBUG)<< "sketching mix(" << patch::to_string(source1) << ", " << patch::to_string(source2) << ", "
	<< patch::to_string(target) + ", " << patch::to_string(volume1) << ", " << patch::to_string(volume2)
	<< ")";

	sketching_transfer(source1, target, volume1);
	sketching_transfer(source2, target, volume2);
}

void Mapping::sketching_loadContainer(int containerID, double volume) {

	LOG(DEBUG)<< "sketching loadContainer(" << patch::to_string(containerID) << ", "
	<< patch::to_string(volume)
	<< ")";

	if (sketch->existsContainer(containerID)) {
		ContainerNode* node = sketch->getContainer(containerID);
		node->setVolume(node->getVolume() + volume);
	} else {
		sketch->addContainer(containerID, boost::shared_ptr<ContainerNodeType>(new ContainerNodeType(MovementType::irrelevant, ContainerType::unknow)), volume);
	}
}

void Mapping::sketching_applyLight(int id, double wavelength,
		double intensity) {

	LOG(DEBUG)<< "sketching applyLight(" << patch::to_string(id) << ", "
	<< patch::to_string(wavelength) << ", " << patch::to_string(intensity)
	<< ")";

	if (sketch->existsContainer(id)) {
		ContainerNode* node = sketch->getContainer(id);
		node->getType().get()->addAddon(AddOnsType::light);
	} else {
		vector<AddOnsType> vect;
		vect.push_back(AddOnsType::light);
		sketch->addContainer(id, boost::shared_ptr<ContainerNodeType>(new ContainerNodeType(MovementType::irrelevant, ContainerType::unknow, vect)), 0.0);
	}
}

void Mapping::sketching_applyTemperature(int id, double degres) {

	LOG(DEBUG)<< "sketching applyTemperature(" << patch::to_string(id) << ", "
	<< patch::to_string(degres) << ")";

	if (sketch->existsContainer(id)) {
		ContainerNode* node = sketch->getContainer(id);
		node->getType().get()->addAddon(AddOnsType::temp);
	} else {
		vector<AddOnsType> vect;
		vect.push_back(AddOnsType::temp);
		sketch->addContainer(id, boost::shared_ptr<ContainerNodeType>(new ContainerNodeType(MovementType::irrelevant, ContainerType::unknow, vect)), 0.0);
	}
}

void Mapping::sketching_measureOD(int id) {

	LOG(DEBUG)<< "sketching measureOD(" << patch::to_string(id) << ")";

	if (sketch->existsContainer(id)) {
		ContainerNode* node = sketch->getContainer(id);
		node->getType().get()->addAddon(AddOnsType::OD_sensor);
	} else {
		vector<AddOnsType> vect;
		vect.push_back(AddOnsType::OD_sensor);
		sketch->addContainer(id, boost::shared_ptr<ContainerNodeType>(new ContainerNodeType(MovementType::irrelevant, ContainerType::unknow, vect)), 0.0);
	}
}

void Mapping::sketching_stir(int id) {
	LOG(DEBUG)<< "sketching measureOD(" << patch::to_string(id) << ")";

	if (sketch->existsContainer(id)) {
		ContainerNode* node = sketch->getContainer(id);
		node->getType().get()->addAddon(AddOnsType::mixer);
	} else {
		vector<AddOnsType> vect;
		vect.push_back(AddOnsType::mixer);
		sketch->addContainer(id, boost::shared_ptr<ContainerNodeType>(new ContainerNodeType(MovementType::irrelevant, ContainerType::unknow, vect)), 0.0);
	}
}

double Mapping::sketching_timeStep() {
	return 1;
}

//TEST
void Mapping::test_setContinuosFlow(int idSource, int idTarget, double rate) {
}

void Mapping::test_transfer(int idSource, int idTarget, double volume) {
}

void Mapping::test_mix(int source1, int source2, int target, double volume1,
		double volume2) {
}

void Mapping::test_applyLight(int id, double wavelength, double intensity) {
}

void Mapping::test_applyTemperature(int id, double degres) {
}

double Mapping::test_getVolume(int id) {
}

double Mapping::test_measureOD(int id) {
}

void Mapping::test_stir(int id, double intensity) {
}

void Mapping::test_loadContainer(int containerID, double volume) {
}

double Mapping::test_timeStep() {
	return 1;
}

//EXEC
void Mapping::exec_setContinuosFlow(int idSource, int idTarget, double rate) {
}

void Mapping::exec_transfer(int idSource, int idTarget, double volume) {
}

void Mapping::exec_mix(int source1, int source2, int target, double volume1,
		double volume2) {
}

void Mapping::exec_applyLight(int id, double wavelength, double intensity) {
}

void Mapping::exec_applyTemperature(int id, double degres) {
}

double Mapping::exec_getVolume(int id) {
}

double Mapping::exec_measureOD(int id) {
}

void Mapping::exec_loadContainer(int containerID, double volume) {
}

void Mapping::exec_stir(int id, double intensity) {
}

double Mapping::exec_timeStep() {
	//TODO: el tiempo que pasa esperando o el sleep en caso de que se haga...
}

void Mapping::printSketch(const std::string& path) {
	sketch->printMachine(path);
}
