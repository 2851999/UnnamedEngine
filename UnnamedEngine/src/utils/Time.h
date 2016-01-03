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

#ifndef UTILS_TIME_H_
#define UTILS_TIME_H_

#include <windows.h>
#include <GL/GLFW/glfw3.h>

/***************************************************************************************************
 * The Time class
 ***************************************************************************************************/

class Time {
public:
	/* NOTE: These methods measure time since the window was created */
	static inline long getTimeSeconds() {
		return (long) (glfwGetTime());
	}

	static inline long getTimeMilliseconds() {
		return (long) (glfwGetTime() * 1000);
	}

	/* This is for windows */
	static inline void sleep(long milliseconds) {
		Sleep(milliseconds);
	}
};

/***************************************************************************************************/

#endif /* UTILS_TIME_H_ */
