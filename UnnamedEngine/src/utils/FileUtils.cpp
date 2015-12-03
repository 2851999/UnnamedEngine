/*****************************************************************************
 *
 *   Copyright 2015 Joel Davies
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *****************************************************************************/

#include "FileUtils.h"

/***************************************************************************************************
 * The FileUtils class
 ***************************************************************************************************/

/* The methods used to read a file and return its contents */
std::string FileUtils::readFileAsString(const char* path) {
	std::ifstream input;
	std::string   output;
	std::string   current;

	input.open(path);

	if (input.is_open()) {
		while (input.good()) {
			getline(input, current);
			output.append(current + "\n");
		}
		input.close();
	} else
		logError("Unable to read the file '" + to_string(path) + "'");
	return output;
}

std::vector<std::string> FileUtils::readFileAsVector(const char* path) {
	std::ifstream            input;
	std::vector<std::string> output;
	std::string              current;

	input.open(path);

	if (input.is_open()) {
		while (input.good()) {
			getline(input, current);
			output.push_back(current);
		}
	} else
		logError("Unable to read the file '" + to_string(path) + "'");
	return output;
}

/***************************************************************************************************/
