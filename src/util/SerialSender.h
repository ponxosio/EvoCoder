/*
 * SerialSender.h
 *
 *  Created on: 7 de may. de 2016
 *      Author: angel
 */

#ifndef SRC_UTIL_SERIALSENDER_H_
#define SRC_UTIL_SERIALSENDER_H_

#include <windows.h>
#include <stdio.h>
#include <string>
#include <ios>

#include "Patch.h"

class SerialSender {
public:
	SerialSender(std::string device,
			DWORD baudRate = CBR_9600,
			BYTE byteSize = 8,
			BYTE stopBits = ONESTOPBIT,
			BYTE parity = NOPARITY,
			DWORD readIntervalTimeout = 500,
			DWORD readTotalTimeoutConstant = 500,
			DWORD readTotalTimeoutMultiplier = 100,
			DWORD writeTotalTimeoutConstant = 500,
			DWORD writeTotalTimeoutMultiplier = 100) throw (std::ios_base::failure);
	virtual ~SerialSender();

	unsigned long sendString(const std::string & str);
	std::string receiveString() throw (std::ios_base::failure);

protected:
	//handler
	HANDLE hSerial;

	//basic settings
	DWORD baudRate;
	BYTE byteSize;
	BYTE stopBits;
	BYTE parity;

	//timeouts
	DWORD readIntervalTimeout;
	DWORD readTotalTimeoutConstant;
	DWORD readTotalTimeoutMultiplier;
	DWORD writeTotalTimeoutConstant;
	DWORD writeTotalTimeoutMultiplier;

	void disconnect();
	void configure() throw (std::ios_base::failure);
};

#endif /* SRC_UTIL_SERIALSENDER_H_ */
