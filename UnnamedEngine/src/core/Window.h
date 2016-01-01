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

#ifndef CORE_WINDOW_H_
#define CORE_WINDOW_H_

/***************************************************************************************************
 * The Window class will create a window with an OpenGL context
 ***************************************************************************************************/

#include <windows.h>
#include <GL/GLEW/glew.h>
#include <GL/GLFW/glfw3.h>

#include "../utils/GLUtils.h"
#include "../utils/Logging.h"
#include "Settings.h"

class Window {
private:
	GLFWwindow* m_instance;
	Settings*   m_settings;
public:
	Window(Settings* settings);
	virtual ~Window();

	static inline bool init() { return glfwInit(); }
	bool create();
	void update();
	void destroy();
	inline void setResizable(bool resizable);
	inline void setDecorated(bool decorated);
	inline void setRefreshRate(int refreshRate);
	inline void setFloating(bool floating);
	inline void setSamples(int samples);
	inline void setVSync(bool vSync);
	inline void setPosition(int x, int y);
	inline void centre();
	inline void makeCurrent();
	bool shouldClose();
	void setKeyCallback(void (* callback)(GLFWwindow*, int , int, int, int));
	void setCharCallback(void (* callback)(GLFWwindow*, unsigned int));
	void setCursorPosCallback(void (* callback)(GLFWwindow*, double, double));
	void setCursorEnterCallback(void (* callback)(GLFWwindow*, int));
	void setMouseButtonCallback(void (* callback)(GLFWwindow*, int, int, int));
	void setScrollCallback(void (* callback)(GLFWwindow*, double, double));
	bool getKey(int key);
	bool getMouseButton(int button);
	inline GLFWwindow* getInstance() { return m_instance; }
};

/***************************************************************************************************/

#endif
