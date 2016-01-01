/*****************************************************************************
 *
 *   Copyright 2015 - 2016 Joel Davies
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

#ifndef CORE_FILEUTILS_H_
#define CORE_FILEUTILS_H_

#include <fstream>
#include <vector>
#include "StringUtils.h"
#include "Logging.h"

/***************************************************************************************************
 * The FileUtils class is responsible for file operations
 ***************************************************************************************************/

class FileUtils {
public:
	static std::string readFileAsString(const char* path);
	static std::vector<std::string> readFileAsVector(const char* path);
};

/***************************************************************************************************/

#endif
