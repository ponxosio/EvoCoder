/*
 * Mapping.h
 *
 *  Created on: 9 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_MAPPING_H_
#define SRC_FLUIDCONTROL_MAPPING_H_

#include <stdexcept>
#include <vector>

//boost
#include <memory>

//lib
#include <easylogging++.h>

//local
#include "../graph/Edge.h"
#include "../graph/Flow.h"
#include "executable/ExecutableMachineGraph.h"
#include "executable/containers/actuators/communications/CommunicationsInterface.h"
#include "executable/containers/actuators/communications/CommandSender.h"
#include "machineGraph/MachineGraph.h"
#include "machineGraph/ContainerNode.h"
#include "MappingEngine.h"

namespace mapping {
/*** Enum for the operation the mapping will do ***/
enum MappingOperation {
	sketch,
	exec_ep,
	exec_general,
};
}

class Mapping {
public:
	Mapping(ExecutableMachineGraph* machine, const std::string & name, const std::vector<int> & communicationInterface);
	virtual ~Mapping();

	//execution
	void setContinuosFlow(int idSource, int idTarget, double rate);
	void transfer(int idSource, int idTarget, double volume);
	void mix(int source1, int source2, int target, double volume1, double volume2);
	void applyLight(int id, double wavelength, double intensity);
	void applyTemperature(int id, double degres);
	void stir(int id, double intensity);
	void loadContainer(int containerID, double volume);

	double getVolume(int id);
	double measureOD(int id);

	double timeStept();

	//operations
	void doMapping() throw (std::invalid_argument);

	bool isSketching();
	void setSketching();

	bool isExec_ep();
	void setExec_ep();

	bool isExec_general();
	void setExec_general();

	//miscellaneous
	void printSketch(const std::string & path);
	void startCommunications();
	void stopCommunications();
protected:
	mapping::MappingOperation operation;
	MappingEngine* engine;
	MachineGraph* sketch;
	ExecutableMachineGraph* machine;
	std::vector<int>* communicationsInterfaces;

	//SKETCHING
	void sketching_setContinuosFlow(int idSource, int idTarget, double rate);
	void sketching_transfer(int idSource, int idTarget, double volume);
	void sketching_mix(int source1, int source2, int target, double volume1,
			double volume2);
	void sketching_applyLight(int id, double wavelength, double intensity);
	void sketching_applyTemperature(int id, double degrees);
	void sketching_stir(int id);
	void sketching_loadContainer(int containerID, double volume);

	void sketching_measureOD(int id);
	double sketching_timeStep();

	void transformSourceContainer(int idSource, int idTarget, std::shared_ptr<ContainerNode> sourceNode, MovementType desiredType);
	void transformTargetContainer(int idSource, int idTarget, std::shared_ptr<ContainerNode> targetNode);

	//EXEC
	void exec_setContinuosFlow(int idSource, int idTarget, double rate);
	void exec_transfer(int idSource, int idTarget, double volume);
	void exec_mix(int source1, int source2, int target, double volume1,
			double volume2);
	void exec_applyLight(int id, double wavelength, double intensity);
	void exec_applyTemperature(int id, double degres);
	void exec_stir(int id, double intensity);
	void exec_loadContainer(int containerID, double volume);

	double exec_getVolume(int id);
	double exec_measureOD(int id);

	double exec_timeStep();
};

#endif /* SRC_FLUIDCONTROL_MAPPING_H_ */
