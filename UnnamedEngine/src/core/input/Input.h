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

#ifndef CORE_INPUT_INPUT_H_
#define CORE_INPUT_INPUT_H_

#include <windows.h>
#include <GL/GLEW/glew.h>
#include <GL/GLFW/glfw3.h>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Controller.h"

/***************************************************************************************************
 * The Mouse class
 ***************************************************************************************************/

class Mouse {
private:
	static bool m_cursorLocked;
public:
	static double lastX;
	static double lastY;
	static bool   leftButtonDown;
	static bool   middleButtonDown;
	static bool   rightMouseDown;

	static bool isPressed(int button);
	static void setPosition(double x, double y);
	static void centre();
	static void lock();
	static void toggleLock();
	static void unlock();
	static inline bool isLocked() { return m_cursorLocked; }
};

/***************************************************************************************************/

/***************************************************************************************************
 * The Keyboard class
 ***************************************************************************************************/

class Keyboard {
private:
public:
	static bool isPressed(int key);
};

/***************************************************************************************************/

/***************************************************************************************************
 * The InputManager class
 ***************************************************************************************************/

class InputListener;

class InputManager {
private:
	static std::vector<Controller*> m_controllers;
	static std::vector<InputListener*> m_listeners;
public:
	static inline void addListener(InputListener* listener) { m_listeners.push_back(listener); }
	static inline void removeListener(InputListener* listener) { m_listeners.erase(std::remove(m_listeners.begin(), m_listeners.end(), listener), m_listeners.end()); }
	static inline void addController(Controller* controller) { m_controllers.push_back(controller); }
	static inline void removeController(Controller* controller) { m_controllers.erase(std::remove(m_controllers.begin(), m_controllers.end(), controller), m_controllers.end()); }
	static void checkInput();
	static void callOnKeyPressed(int code);
	static void callOnKeyReleased(int code);
	static void callOnKeyTyped(int code);
	static void callOnChar(int code, char character);
	static void callOnMousePressed(int button);
	static void callOnMouseReleased(int button);
	static void callOnMouseClicked(int button);
	static void callOnMouseMoved(double x, double y, double dx, double dy);
	static void callOnMouseDragged(double x, double y, double dx, double dy);
	static void callOnMouseEnter();
	static void callOnMouseLeave();
	static void callOnScroll(double dx, double dy);
	static void callOnControllerButtonPressed(ControllerButton* button);
	static void callOnControllerButtonReleased(ControllerButton* button);
	static void callOnControllerAxisChange(ControllerAxis* axis);
};

/***************************************************************************************************/

/***************************************************************************************************
 * The InputListener class
 ***************************************************************************************************/

class InputListener {
public:
	InputListener() {}
	virtual ~InputListener() {}

	inline void addListener() { InputManager::addListener(this); }
	//inline void removeListener() { InputManager::removeListener(*this); }

	virtual void onKeyPressed(int code) {}
	virtual void onKeyReleased(int code) {}
	virtual void onKeyTyped(int code) {}
	virtual void onChar(int code, char character) {}

	virtual void onMousePressed(int button) {}
	virtual void onMouseReleased(int button) {}
	virtual void onMouseClicked(int button) {}
	virtual void onMouseMoved(double x, double y, double dx, double dy) {}
	virtual void onMouseDragged(double x, double y, double dx, double dy) {}
	virtual void onMouseEnter() {}
	virtual void onMouseLeave() {}

	virtual void onScroll(double dx, double dy) {}

	virtual void onControllerButtonPressed(ControllerButton* button) {}
	virtual void onControllerButtonReleased(ControllerButton* button) {}
	virtual void onControllerAxisChange(ControllerAxis* axis) {}
};

/***************************************************************************************************/

/***************************************************************************************************
 * The various input callbacks
 ***************************************************************************************************/

void input_callback_key(GLFWwindow* window, int key, int scancode, int action, int mods);
void input_callback_char(GLFWwindow* winodw, unsigned int codepoint);
void input_callback_cursorPosition(GLFWwindow* window, double xpos, double ypos);
void input_callback_cursorEnter(GLFWwindow* window, int entered);
void input_callback_mouseButton(GLFWwindow* window, int button, int action, int mods);
void input_callback_scroll(GLFWwindow* window, double xoffset, double yoffset);

/***************************************************************************************************/

#endif /* CORE_INPUT_INPUT_H_ */
