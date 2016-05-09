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

#include "../../lib/easylogging++.h"

#include "Patch.h"

/**
 * Class that makes the serial communication
 */
class SerialSender {
public:
	/**
	 * @param device name of the port to communicate to (ex. \\\\.\\COM3)
	 *
	 * @param baudRate Specifies the baud at which the communications device operates (9600 default).
	 * @param byteSize Size of a byte (8 default).
	 * @param stopBits Specifies the number of stop bits to be used. This member can be one of the following values:
	 * 			ONESTOPBIT, ONE5STOPBITS, TWOSTOPBITS (ONESTOPBIT default)
	 * @param parity Specifies the parity scheme to be used. This member can be one of the following values:
	 * 			EVENPARITY, MARKPARITY, NOPARITY, ODDPARITY (NOPARITY default).

	 * @param maxMsWaitingRead maximum time waiting for data to arrive when performing a readString operation, if this
	 * 			this time is surpassed a timeout exception will be thrown (10000 default).
	 * @param readIntervalTimeout Specify time-out between character for receiving (50 default).
	 * @param readTotalTimeoutConstant Specify value that is multiplied by the requested number
	 * 			of bytes to be read (50 default).
	 * @param readTotalTimeoutMultiplier Specify value is added to the product of the
	 * 			ReadTotalTimeoutMultiplier member (10 default).
	 * @param writeTotalTimeoutConstant Specify value that is multiplied by the requested number
	 * 			of bytes to be sent (50 default).
	 * @param writeTotalTimeoutMultiplier Specify value is added to the product of the
	 * 			WriteTotalTimeoutMultiplier member (10 default).
	 */
	SerialSender(std::string device,
			DWORD baudRate = CBR_9600,
			BYTE byteSize = 8,
			BYTE stopBits = ONESTOPBIT,
			BYTE parity = NOPARITY,
			DWORD maxMsWaitingRead = 10000,
			DWORD readIntervalTimeout = 50,
			DWORD readTotalTimeoutConstant = 50,
			DWORD readTotalTimeoutMultiplier = 10,
			DWORD writeTotalTimeoutConstant = 50,
			DWORD writeTotalTimeoutMultiplier = 10)
					throw (std::ios_base::failure);
	virtual ~SerialSender();

	/**
	 * Send the string through the serial port.
	 * @param str the number of characters send.
	 */
	unsigned long sendString(const std::string & str);
	/**
	 * receive a String through the serial port. if no information after maxMsWaitingRead millisenconds
	 * a timeout exception is thrown.
	 * @return the received string.
	 */
	std::string receiveString() throw (std::ios_base::failure);

protected:
	//handler
	/**
	 * Makes the serial communication
	 */
	HANDLE hSerial;

	//basic settings
	/**
	 * Specifies the baud at which the communications device operates
	 */
	DWORD baudRate;
	/**
	 * Size of a byte
	 */
	BYTE byteSize;
	/**
	 * Specifies the number of stop bits to be used. This member can be one of the following values:
	 * ONESTOPBIT, ONE5STOPBITS, TWOSTOPBITS
	 */
	BYTE stopBits;
	/**
	 * Specifies the parity scheme to be used. This member can be one of the following values:
	 * EVENPARITY, MARKPARITY, NOPARITY, ODDPARITY
	 */
	BYTE parity;

	//timeouts
	/**
	 * maximum time waiting for data to arrive when performing a readString operation, if this
	 * this time is surpassed a timeout exception will be thrown.
	 */
	DWORD maxMsWaitingRead;

	//internal
	/**
	 * Specify time-out between character for receiving.
	 */
	DWORD readIntervalTimeout;
	/**
	 * Specify value that is multiplied by the requested number of bytes to be read.
	 */
	DWORD readTotalTimeoutConstant;
	/**
	 * Specify value is added to the product of the ReadTotalTimeoutMultiplier member.
	 */
	DWORD readTotalTimeoutMultiplier;
	/**
	 * Specify value that is multiplied by the requested number of bytes to be sent.
	 */
	DWORD writeTotalTimeoutConstant;
	/**
	 * Specify value is added to the product of the WriteTotalTimeoutMultiplier member
	 */
	DWORD writeTotalTimeoutMultiplier;

	void disconnect();
	void configure() throw (std::ios_base::failure);
};

#endif /* SRC_UTIL_SERIALSENDER_H_ */
