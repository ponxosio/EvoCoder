/*
 * SerialSender.cpp
 *
 *  Created on: 7 de may. de 2016
 *      Author: angel
 */

#include "SerialSender.h"

SerialSender::SerialSender(std::string device,
		DWORD baudRate,
		BYTE byteSize,
		BYTE stopBits,
		BYTE parity,
		long maxMsWaitingRead,
		DWORD readIntervalTimeout,
		DWORD readTotalTimeoutConstant,
		DWORD readTotalTimeoutMultiplier,
		DWORD writeTotalTimeoutConstant,
		DWORD writeTotalTimeoutMultiplier)
				throw (std::ios_base::failure) {

	this->baudRate = baudRate;
	this->byteSize = byteSize;
	this->stopBits = stopBits;
	this->parity = parity;

	this->maxMsWaitingRead = maxMsWaitingRead;
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
	LOG(DEBUG) << "send  " << bytesWritten << " bytes";

	return bytesWritten;
}

std::string SerialSender::receiveString() throw (std::ios_base::failure) {
	long waited = 0;
	DWORD dwErrorFlags;
	COMSTAT ComStat;

	ClearCommError(hSerial, &dwErrorFlags, &ComStat);

	while (ComStat.cbInQue == 0) {
		LOG(DEBUG) << "waiting for data for " << waited << " ms";
		Sleep(100);
		waited += 100;
		ClearCommError(hSerial, &dwErrorFlags, &ComStat);
		if (waited >= maxMsWaitingRead) {
			throw(std::ios_base::failure("timeout while reading data"));
		}
	}

	DWORD bytesRead;
	std::string buffer;
	char tempChar;
	ReadFile(hSerial,           //Handle of the Serial port
			&tempChar,       //Temporary character
			sizeof(tempChar),       //Size of TempChar
			&bytesRead,    //Number of bytes read
			NULL);

	while (bytesRead > 0) {
		buffer += tempChar;    // Store Tempchar into buffer
		LOG(DEBUG)<< "read " << bytesRead << " bytes";
		ReadFile(hSerial,           //Handle of the Serial port
				&tempChar,       //Temporary character
				sizeof(tempChar),       //Size of TempChar
				&bytesRead,    //Number of bytes read
				NULL);

	}
	return buffer;
}

void SerialSender::configure() throw (std::ios_base::failure) {
	//params
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(DCB);

	if (!GetCommState(hSerial, &dcbSerialParams)) {
		throw( std::ios_base::failure(
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