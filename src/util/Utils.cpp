/*
 * Utils.cpp
 *
 *  Created on: 3 de mar. de 2016
 *      Author: angel
 */

#include "Utils.h"

Utils::Utils() {
	// TODO Auto-generated constructor stub

}

Utils::~Utils() {
	// TODO Auto-generated destructor stub
}

string Utils::getCurrentDir() {
	string vuelta = "";
	char win32[FILENAME_MAX];

	if (GetCurrentDir(win32, sizeof(win32))) {
		vuelta = string(win32);
	} else {
		LOG(ERROR) << "Graph::saveGraph-> unable to retrieve current directory"
				<< endl;
	}
	return vuelta;
}

void Utils::tokenize(const string& str,
                      vector<string>& tokens,
                      const string& delimiters)
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}
