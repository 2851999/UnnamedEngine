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

#ifndef CORE_LOGGING_H_
#define CORE_LOGGING_H_

#include <string>
#include <iostream>

/* Define the types of logs */
enum {
	LOG_INFORMATION,
	LOG_WARNING,
	LOG_ERROR,
	LOG_DEBUG
};

/* The various values that determine which logs will be printed */
static bool LOGGER_DEBUG_ENABLED       = true;
static bool LOGGER_INFORMATION_ENABLED = true;
static bool LOGGER_WARNING_ENABLED     = true;
static bool LOGGER_ERROR_ENABLED       = true;


/***************************************************************************************************
 * The Log class stores data that can be print a log
 ***************************************************************************************************/
class Log {
private:
	std::string m_message;
	int         m_type;
public:
	Log(std::string message, int type): m_message(message), m_type(type) {}
	inline int         getType()       { return m_type;    }
	inline std::string getMessage()    { return m_message; }
	inline bool        isInformation() { return m_type == LOG_INFORMATION; }
	inline bool        isWarning()     { return m_type == LOG_WARNING;     }
	inline bool        isError()       { return m_type == LOG_ERROR;       }
	inline bool        isDebug()       { return m_type == LOG_DEBUG;       }
};

/***************************************************************************************************/

/* The methods used to print out a message */
inline void print(std::string message)   { std::cout << message;              }
inline void println(std::string message) { std::cout << message << std::endl; }

/* Define the methods to print out a log */
static void log(Log log) {
	if (log.isDebug() && LOGGER_DEBUG_ENABLED)
		println("[DEBUG] " + log.getMessage());
	else if (log.isInformation() && LOGGER_INFORMATION_ENABLED)
		println("[INFORMATION] " + log.getMessage());
	else if (log.isWarning() && LOGGER_WARNING_ENABLED)
		println("[WARNING] " + log.getMessage());
	else if (log.isError() && LOGGER_ERROR_ENABLED)
		println("[ERROR] " + log.getMessage());
}

/* The various other utility methods to construct and print a log */
inline void logDebug(std::string message) {
	log(Log(message, LOG_DEBUG));
}

inline void logInformation(std::string message) {
	log(Log(message, LOG_INFORMATION));
}

inline void logWarning(std::string message) {
	log(Log(message, LOG_WARNING));
}

inline void logError(std::string message) {
	log(Log(message, LOG_ERROR));
}

#endif
