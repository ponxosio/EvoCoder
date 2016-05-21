/*
 * ProtocolGraph.cpp
 *
 *  Created on: 9 de mar. de 2016
 *      Author: angel
 */

#include "MachineGraph.h"

using namespace std;

MachineGraph::MachineGraph(string name) {
	this->name = name;
	this->machine = new Graph<ContainerNode, Edge>();
}

MachineGraph::~MachineGraph() {
	delete machine;
}

bool MachineGraph::addContainer(int idContainer, std::shared_ptr<ContainerNodeType> type,
		float capacity) {
	bool vuelta = false;
	if (!existsContainer(idContainer)) {
		machine->addNode(std::make_shared<ContainerNode>(new ContainerNode(idContainer, type, capacity)));
		vuelta = true;
	}
	return vuelta;
}

bool MachineGraph::connectContainer(int idSource, int idTarget) {
	bool vuelta = false;
	if (existsContainer(idSource) && existsContainer(idTarget)
			&& !areConected(idSource, idTarget)) {
		machine->addEdge(std::make_shared<Edge>(new Edge(idSource, idTarget)));
		vuelta = true;
	}
	return vuelta;
}

float MachineGraph::getVolume(int idContainer) {
	float vuelta = -1.0f;
	try {
		std::shared_ptr<ContainerNode> cont = machine->getNode(idContainer);
		vuelta = cont->getVolume();
	} catch (std::invalid_argument& e) {
		LOG(ERROR) << "error while getting volume, " + e.what();
	}
	return vuelta;
}

bool MachineGraph::addVolume(int idContainer, float volume) {
	bool vuelta = false;

	try {
		std::shared_ptr<ContainerNode> cont = machine->getNode(idContainer);
		if ((cont->getVolume() + volume) <= cont->getCapacity()) {
			cont->setVolume(cont->getVolume() + volume);
			vuelta = true;
		} else {
			LOG(WARNING)<< " container "
			<< patch::to_string(cont->getContainerId())
			<< " is fill over capacity";
		}
	} catch (std::invalid_argument& e) {
		LOG(ERROR) << "error while adding volume, " + e.what();
	}

	return vuelta;
}

bool MachineGraph::extractVolume(int idContainer, float volume) {
	bool vuelta = false;

	ContainerNode* cont = machine->getNode(idContainer);
	if (cont != NULL) {
		if ((cont->getVolume() - volume) >= 0) {
			cont->setVolume(cont->getVolume() + volume);
			vuelta = true;
		} else {
			LOG(WARNING) << " container "
					<< patch::to_string(cont->getContainerId()) << " has "
					<< patch::to_string(cont->getVolume())
					<< " trying to extract " << patch::to_string(volume);
		}
	}
	return vuelta;
}

bool MachineGraph::areConected(int idSource, int idTarget) {
	return machine->areConnected(idSource, idTarget);
}

bool MachineGraph::hasConections(int idContainer) {
	bool vuelta = false;
	try {
		shared_ptr<ContainerNode> cont = machine->getNode(idContainer);
		const vector<shared_ptr<Edge>> neighbors = machine->getLeavingEdges(
				idContainer);
		vuelta = !neighbors.empty();
	} catch (std::invalid_argument& e) {
		LOG(ERROR)<< e.what();
	}

	return vuelta;
}

bool MachineGraph::changeContainerType(int idContainer, ContainerType type) {
	bool vuelta = false;

	try {
		shared_ptr<ContainerNode> cont = machine->getNode(idContainer);
		cont->changeContainerType(type);
		vuelta = true;
	} catch (std::invalid_argument& e) {
		LOG(ERROR)<< e.what();
	}

	return vuelta;
}

bool MachineGraph::changeMovementType(int idContainer, MovementType type) {
	bool vuelta = false;
	try {
		shared_ptr<ContainerNode> cont = machine->getNode(idContainer);
		cont->changeMovementType(type);
		vuelta = true;
	} catch (std::invalid_argument& e) {
		LOG(ERROR)<< e.what();
	}
	return vuelta;
}

bool MachineGraph::addAddon(int idContainer, AddOnsType type) {
	bool vuelta = false;
	try {
		shared_ptr<ContainerNode> cont = machine->getNode(idContainer);
		cont->addAddon(type);
		vuelta = true;
	} catch (std::invalid_argument& e) {
		LOG(ERROR)<< e.what();
	}
	return vuelta;
}

bool MachineGraph::removeAddon(int idContainer, AddOnsType type) {
	bool vuelta = false;
	try {
		shared_ptr<ContainerNode> cont = machine->getNode(idContainer);
		cont->removeAddon(type);
		vuelta = true;
	} catch (std::invalid_argument& e) {
		LOG(ERROR)<< e.what();
	}
	return vuelta;
}

void MachineGraph::printMachine(const std::string& path) {
	machine->saveGraph(path);
}
