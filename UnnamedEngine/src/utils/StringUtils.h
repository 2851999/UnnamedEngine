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

#ifndef CORE_STRINGUTILS_H_
#define CORE_STRINGUTILS_H_

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

/***************************************************************************************************
 * Method used to convert a value to a string
 ***************************************************************************************************/

template<typename T>
inline std::string to_string(T value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

template<typename T1, typename T2>
inline std::string string_join(T1 a, T2 b) {
	std::stringstream ss;
	ss << a << b;
	return ss.str();
}

inline bool string_endsWith(std::string value, std::string ending) {
	return value.compare(value.length() - ending.length(), ending.length(), ending) == 0;
}

inline std::string string_toLowerCase(std::string value) {
	std::transform(value.begin(), value.end(), value.begin(), ::tolower);
	return value;
}

inline std::vector<std::string> split_string(const std::string &s, char delimeter) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> split;
	while (std::getline(ss, item, delimeter))
		split.push_back(item);
	return split;
}

inline std::string split_string_last(const std::string &s, char delimeter) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> split;
	while (std::getline(ss, item, delimeter))
		split.push_back(item);
	return split.at(split.size() - 1);
}

inline std::string substring(const std::string &s, int begin, int end) {
	return s.substr(begin, end - begin);
}

/***************************************************************************************************/

#endif
