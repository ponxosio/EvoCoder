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

bool MachineGraph::addContainer(int idContainer, NodeType type,
		float capacity) {
	bool vuelta = false;
	if (!existsContainer(idContainer)) {
		ContainerNode* newNode = new ContainerNode(idContainer, type, capacity);
		machine->addNode(newNode);
		vuelta = true;
	}
	return vuelta;
}

bool MachineGraph::connectContainer(int idSource, int idTarget) {
	bool vuelta = false;
	if (existsContainer(idSource) && existsContainer(idTarget)
			&& !areConected(idSource, idTarget)) {
		Edge* newEdge = new Edge(idSource, idTarget);
		machine->addEdge(newEdge);
		vuelta = true;
	}
	return vuelta;
}

bool MachineGraph::changeContainerType(int idContainer, NodeType type) {
	bool vuelta = false;

	ContainerNode* cont = machine->getNode(idContainer);
	if (cont != NULL) {
		cont->setType(type);
		vuelta = true;
	}
	return vuelta;
}

float MachineGraph::getVolume(int idContainer) {
	float vuelta = -1.0f;

	ContainerNode* cont = machine->getNode(idContainer);
	if (cont != NULL) {
		vuelta = cont->getVolume();
	}
	return vuelta;
}

bool MachineGraph::addVolume(int idContainer, float volume) {
	bool vuelta = false;

	ContainerNode* cont = machine->getNode(idContainer);
	if (cont != NULL) {
		if ((cont->getVolume() + volume) <= cont->getCapacity()) {
			cont->setVolume(cont->getVolume() + volume);
			vuelta = true;
		} else {
			LOG(WARNING) << " container "
					<< patch::to_string(cont->getContainerId())
					<< " is fill over capacity";
		}
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
	bool vuelta = false;
	const vector<Edge*>* neighbors = machine->getNeighbors(idSource);

	auto it = neighbors->begin();
	while (!vuelta && (it != neighbors->end())) {
		Edge* cast = *it;
		vuelta = (cast->getIdTarget() == idTarget);
	}
	return vuelta;
}

bool MachineGraph::hasConections(int idContainer) {
	bool vuelta = false;
	ContainerNode* cont = machine->getNode(idContainer);

	if (cont != NULL) {
		const vector<Edge*>* neighbors = machine->getNeighbors(idContainer);
		vuelta = !neighbors->empty();
	}
	return vuelta;
}

void MachineGraph::printMachine(const std::string& path) {
	machine->saveGraph(path);
}
