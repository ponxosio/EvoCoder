/*
 * FileSender.h
 *
 *  Created on: 15 de may. de 2016
 *      Author: angel
 */

#ifndef FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_COMMUNICATIONS_FILESENDER_H_
#define FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_COMMUNICATIONS_FILESENDER_H_

#include <iostream>
#include <fstream>
#include <ios>
#include <cfloat>
#include <string>

#include "CommandSender.h"

class FileSender: public CommandSender {
public:
	FileSender(const std::string & outputName, const std::string & inputName);
	virtual ~FileSender();

	virtual unsigned long sendString(const std::string & str);
	virtual std::string receiveString() throw (std::ios_base::failure);
	virtual std::string readUntil(char endCharacter)
			throw (std::ios_base::failure);
	virtual void disconnect();
	virtual void connect() throw (std::ios_base::failure);
	inline virtual void synch() throw (std::ios_base::failure){};

protected:
	std::string outputName;
	std::string inputName;

	std::ofstream outFile;
	std::ifstream inFile;
};

#endif /* FLUIDCONTROL_EXECUTABLE_CONTAINERS_ACTUATORS_COMMUNICATIONS_FILESENDER_H_ */
