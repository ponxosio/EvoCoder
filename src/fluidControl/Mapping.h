/*
 * Mapping.h
 *
 *  Created on: 9 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_FLUIDCONTROL_MAPPING_H_
#define SRC_FLUIDCONTROL_MAPPING_H_

//lib
#include "../../lib/easylogging++.h"

//local
#include "machineGraph/MachineGraph.h"
#include "machineGraph/ExecutableMachineGraph.h"

namespace mapping {
/*** Enum for the operation the mapping will do ***/
enum MappingOperation {
	sketch,
	test,
	exec_ep,
	exec_general,
};
}

class Mapping {
public:
	Mapping(ExecutableMachineGraph* machine, const std::string & name);
	virtual ~Mapping();

	//execution
	void setContinuosFlow(int idSource, int idTarget, double rate);
	void transfer(int idSource, int idTarget, double volume);
	void mix(int source1, int source2, int target, double volume1, double volume2);
	void applyLight(int id, double wavelength, double intensity);
	void applyTemperature(int id, double degres);
	void loadContainer(int containerID, double volume);

	double getVolume(int id);
	double measureOD(int id);

	double timeStept();

	//operations
	bool isSketching();
	void setSketching();

	bool isTest();
	void setTest();

	bool isExec_ep();
	void setExec_ep();

	bool isExec_general();
	void setExec_general();

	//miscellaneous
	void printSketch(const std::string & path);

protected:
	mapping::MappingOperation operation;
	MachineGraph* sketch;
	ExecutableMachineGraph* machine;

	//SKETCHING
	void sketching_setContinuosFlow(int idSource, int idTarget, double rate);
	void sketching_transfer(int idSource, int idTarget, double volume);
	void sketching_mix(int source1, int source2, int target, double volume1,
			double volume2);
	void sketching_applyLight(int id, double wavelength, double intensity);
	void sketching_applyTemperature(int id, double degrees);
	void sketching_loadContainer(int containerID, double volume);

	double sketching_measureOD(int id);
	double sketching_timeStep();

	//TEST
	void test_setContinuosFlow(int idSource, int idTarget, double rate);
	void test_transfer(int idSource, int idTarget, double volume);
	void test_mix(int source1, int source2, int target, double volume1,
			double volume2);
	void test_applyLight(int id, double wavelength, double intensity);
	void test_applyTemperature(int id, double degres);
	void test_loadContainer(int containerID, double volume);

	double test_getVolume(int id);
	double test_measureOD(int id);

	double test_timeStep();
	//EXEC
	void exec_setContinuosFlow(int idSource, int idTarget, double rate);
	void exec_transfer(int idSource, int idTarget, double volume);
	void exec_mix(int source1, int source2, int target, double volume1,
			double volume2);
	void exec_applyLight(int id, double wavelength, double intensity);
	void exec_applyTemperature(int id, double degres);
	void exec_loadContainer(int containerID, double volume);

	double exec_getVolume(int id);
	double exec_measureOD(int id);

	double exec_timeStep();
};

#endif /* SRC_FLUIDCONTROL_MAPPING_H_ */
