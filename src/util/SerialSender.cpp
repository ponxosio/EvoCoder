/*
 * SerialSender.cpp
 *
 *  Created on: 7 de may. de 2016
 *      Author: angel
 */

#include "SerialSender.h"

SerialSender::SerialSender(std::string device, unsigned long baudRate,
		unsigned char byteSize, unsigned char stopBits, unsigned char parity,
		unsigned long readIntervalTimeout,
		unsigned long readTotalTimeoutConstant,
		unsigned long readTotalTimeoutMultiplier,
		unsigned long writeTotalTimeoutConstant,
		unsigned long writeTotalTimeoutMultiplier)
				throw (std::ios_base::failure) {

	this->baudRate = baudRate;
	this->byteSize = byteSize;
	this->stopBits = stopBits;
	this->parity = parity;

	this->readIntervalTimeout = readIntervalTimeout;
	this->readTotalTimeoutConstant = readTotalTimeoutConstant;
	this->readTotalTimeoutMultiplier = readTotalTimeoutMultiplier;
	this->writeTotalTimeoutConstant = writeTotalTimeoutConstant;
	this->writeTotalTimeoutMultiplier = writeTotalTimeoutMultiplier;

	hSerial = CreateFile(device.c_str(),
	GENERIC_READ | GENERIC_WRITE, 0, 0,
	OPEN_EXISTING,
	0, 0);

	if (hSerial == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
			throw(std::ios_base::failure(
					"device " + device + " does not exists"));
		}
		throw(std::ios_base::failure("can not open the connection"));
	}

	configure();
}

SerialSender::~SerialSender() {
	disconnect();
}

void SerialSender::disconnect() {
	CloseHandle(hSerial);
}

unsigned long SerialSender::sendString(const std::string& str) {
	DWORD bytesWritten = 0;
	WriteFile(hSerial, str.c_str(), sizeof(char) * str.length(), &bytesWritten, NULL);

	return bytesWritten;
}

std::string SerialSender::receiveString() throw (std::ios_base::failure) {
	DWORD dwEventMask;
	if (!WaitCommEvent(hSerial, &dwEventMask, NULL)) {
		//error
	}

	DWORD bytesRead;
	int i = 0;
	std::string buffer;
	char tempChar;

	do {
		ReadFile(hSerial,           //Handle of the Serial port
				&tempChar,       //Temporary character
				sizeof(tempChar),       //Size of TempChar
				&bytesRead,    //Number of bytes read
				NULL);

		buffer += tempChar;    // Store Tempchar into buffer
	} while (bytesRead > 0);

	return buffer;
}

void SerialSender::configure() throw (std::ios_base::failure) {
	//params
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(DCB);

	if (!GetCommState(hSerial, &dcbSerialParams)) {
		throw(new std::ios_base::failure(
				"Failed to Get Comm State Reason: " + GetLastError()));
	}
	dcbSerialParams.BaudRate = baudRate;
	dcbSerialParams.ByteSize = byteSize;
	dcbSerialParams.StopBits = stopBits;
	dcbSerialParams.Parity = parity;

	if (!SetCommState(hSerial, &dcbSerialParams)) {
		throw(std::ios_base::failure(
				"Failed to set Comm state reason: " + GetLastError()));
	}

	//timeouts
	COMMTIMEOUTS timeouts = { 0 };

	timeouts.ReadIntervalTimeout = readIntervalTimeout;
	timeouts.ReadTotalTimeoutConstant = readTotalTimeoutConstant;
	timeouts.ReadTotalTimeoutMultiplier = readTotalTimeoutMultiplier;
	timeouts.WriteTotalTimeoutConstant = writeTotalTimeoutConstant;
	timeouts.WriteTotalTimeoutMultiplier = writeTotalTimeoutMultiplier;

	if (!SetCommTimeouts(hSerial, &timeouts)) {
		throw(std::ios_base::failure(
				"Failed to set TimeOuts reason: " + GetLastError()));
	}

	if (!SetCommMask(hSerial, EV_TXEMPTY | EV_RXCHAR)) {
		throw(std::ios_base::failure(
				"Failed to set Comm mask, reason: " + GetLastError()));
	}
}
