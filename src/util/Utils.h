/*
 * Utils.h
 *
 *  Created on: 3 de mar. de 2016
 *      Author: angel
 */

#ifndef SRC_UTIL_UTILS_H_
#define SRC_UTIL_UTILS_H_

#include <stdio.h>
#include <sys/time.h>
#include <string>
#include <iostream>
#include <sstream>

#include <vector>

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

//local
#include "../../lib/easylogging++.h"

using namespace std;

/**
 * Class only eith static methods that do miscelaneus staff
 */
class Utils {

public:
	/**
	 * Divides a string into chunks separating by a delimeter.
	 * @param str string to be divided
	 * @param tokens vector where the chunks will be returned
	 * @param delimeter string that represents where to cut.
	 */
	static void tokenize(const string& str, vector<string> &tokens, const string& delimeter = " ");
	/**
	 * Return the path of the current directory where the program is running
	 * @return a string with the path of the current directory where the program is running if no error has occurred,
	 * an empty one otherwise.
	 */
	static string getCurrentDir();
	/**
	 * Initialize the log library, call this method only once. Receives the arguments of the main function
	 * @param argc number of arguments passed to the main method
	 * @param argv array of arguments passed to the main method
	 */
	static void initLogs(int argc, const char** argv);
	/**
	 * return the current timestamp in Milliseconds since epoch time
	 */
	static long getCurrentTimeMilis();

	/**
	 * Checks if an object can be cast to a given subtype,
	 *
	 * USE ONLY WITH POLYMORFYC TYPES
	 * @param src pointer to the object trying to be casted
	 * @return true if the object can be casted, false otherwise
	 */
	template<class DstType, class SrcType>
	static bool IsType(const SrcType* src) {
		return dynamic_cast<const DstType*>(src) != 0;
	}

private:
	Utils();
	virtual ~Utils();
};



#endif /* SRC_UTIL_UTILS_H_ */
