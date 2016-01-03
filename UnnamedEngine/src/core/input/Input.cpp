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

#include "Input.h"

#include "../BaseEngine.h"

/***************************************************************************************************
 * The Mouse class
 ***************************************************************************************************/

bool Mouse::m_cursorLocked = false;
double Mouse::lastX = -1;
double Mouse::lastY = -1;
bool Mouse::leftButtonDown = false;
bool Mouse::middleButtonDown = false;
bool Mouse::rightMouseDown = false;

bool Mouse::isPressed(int button) {
	int state = glfwGetMouseButton(BaseEngine::current->getWindow()->getInstance(), button);
	return state == GLFW_PRESS || (BaseEngine::current->getSettings()->getMouseEventsRepeat() && state == GLFW_REPEAT);
}

void Mouse::setPosition(double x, double y) {
	glfwSetCursorPos(BaseEngine::current->getWindow()->getInstance(), x, y);
}

void Mouse::centre() {
	setPosition(BaseEngine::current->getSettings()->getWindowWidth() / 2, BaseEngine::current->getSettings()->getWindowHeight() / 2);
}

void Mouse::lock() {
	glfwSetInputMode(BaseEngine::current->getWindow()->getInstance(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	m_cursorLocked = true;
}

void Mouse::toggleLock() {
	if (m_cursorLocked)
		unlock();
	else
		lock();
}

void Mouse::unlock() {
	glfwSetInputMode(BaseEngine::current->getWindow()->getInstance(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	m_cursorLocked = false;
	centre();
}

/***************************************************************************************************/

/***************************************************************************************************
 * The Keyboard class
 ***************************************************************************************************/

bool Keyboard::isPressed(int key) {
	int state = glfwGetKey(BaseEngine::current->getWindow()->getInstance(), key);
	return state == GLFW_PRESS || (BaseEngine::current->getSettings()->getKeyboardEventsRepeat() && state == GLFW_REPEAT);
}

/***************************************************************************************************/

/***************************************************************************************************
 * The InputManager class
 ***************************************************************************************************/

std::vector<Controller*> InputManager::m_controllers;
std::vector<InputListener*> InputManager::m_listeners;

void InputManager::checkInput() {
	for (unsigned int a = 0; a < m_controllers.size(); a++)
		m_controllers.at(a)->checkInput();
}

void InputManager::callOnKeyPressed(int code) {
	for (unsigned int a = 0; a < m_listeners.size(); a++)
		m_listeners[a]->onKeyPressed(code);
}

void InputManager::callOnKeyReleased(int code) {
	for (unsigned int a = 0; a < m_listeners.size(); a++)
		m_listeners[a]->onKeyReleased(code);
}

void InputManager::callOnKeyTyped(int code) {
	for (unsigned int a = 0; a < m_listeners.size(); a++)
		m_listeners[a]->onKeyTyped(code);
}

void InputManager::callOnChar(int code, char character) {
	for (unsigned int a = 0; a < m_listeners.size(); a++)
		m_listeners[a]->onChar(code, character);
}

void InputManager::callOnMousePressed(int code) {
	for (unsigned int a = 0; a < m_listeners.size(); a++)
		m_listeners[a]->onMousePressed(code);
}

void InputManager::callOnMouseReleased(int code) {
	for (unsigned int a = 0; a < m_listeners.size(); a++)
		m_listeners[a]->onMouseReleased(code);
}

void InputManager::callOnMouseClicked(int code) {
	for (unsigned int a = 0; a < m_listeners.size(); a++)
		m_listeners[a]->onMouseClicked(code);
}

void InputManager::callOnMouseMoved(double x, double y, double dx, double dy) {
	for (unsigned int a = 0; a < m_listeners.size(); a++)
		m_listeners[a]->onMouseMoved(x, y, dx, dy);
}

void InputManager::callOnMouseDragged(double x, double y, double dx, double dy) {
	for (unsigned int a = 0; a < m_listeners.size(); a++)
		m_listeners[a]->onMouseDragged(x, y, dx, dy);
}

void InputManager::callOnMouseEnter() {
	for (unsigned int a = 0; a < m_listeners.size(); a++)
		m_listeners[a]->onMouseEnter();
}

void InputManager::callOnMouseLeave() {
	for (unsigned int a = 0; a < m_listeners.size(); a++)
		m_listeners[a]->onMouseLeave();
}

void InputManager::callOnScroll(double dx, double dy) {
	for (unsigned int a = 0; a < m_listeners.size(); a++)
		m_listeners[a]->onScroll(dx, dy);
}

void InputManager::callOnControllerButtonPressed(ControllerButton* button) {
	for (unsigned int a = 0; a < m_listeners.size(); a++)
		m_listeners[a]->onControllerButtonPressed(button);
}

void InputManager::callOnControllerButtonReleased(ControllerButton* button) {
	for (unsigned int a = 0; a < m_listeners.size(); a++)
		m_listeners[a]->onControllerButtonReleased(button);
}

void InputManager::callOnControllerAxisChange(ControllerAxis* button) {
	for (unsigned int a = 0; a < m_listeners.size(); a++)
		m_listeners[a]->onControllerAxisChange(button);
}

/***************************************************************************************************/

/***************************************************************************************************
 * The various input callbacks
 ***************************************************************************************************/

void input_callback_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS || (BaseEngine::current->getSettings()->getKeyboardEventsRepeat() && action == GLFW_REPEAT)) {
		InputManager::callOnKeyPressed(key);
	} else if (action == GLFW_RELEASE) {
		InputManager::callOnKeyReleased(key);
		InputManager::callOnKeyTyped(key);
	}
}

void input_callback_char(GLFWwindow* window, unsigned int codepoint) {
	InputManager::callOnChar(codepoint, (char) codepoint);
}

void input_callback_mouseButton(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS || (BaseEngine::current->getSettings()->getMouseEventsRepeat() && action == GLFW_REPEAT)) {
		if (button == GLFW_MOUSE_BUTTON_LEFT)
			Mouse::leftButtonDown = true;
		else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
			Mouse::middleButtonDown = true;
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
			Mouse::rightMouseDown = true;
		InputManager::callOnMousePressed(button);
	} else if (action == GLFW_RELEASE) {
		if (button == GLFW_MOUSE_BUTTON_LEFT)
			Mouse::leftButtonDown = false;
		else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
			Mouse::middleButtonDown = false;
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
			Mouse::rightMouseDown = false;
		InputManager::callOnMouseReleased(button);
		InputManager::callOnMouseClicked(button);
	}
}

void input_callback_cursorPosition(GLFWwindow* window, double xpos, double ypos) {
	double xOffset = xpos - Mouse::lastX;
	double yOffset = ypos - Mouse::lastY;
	if (Mouse::lastX == -1) {
		xOffset = 0;
		yOffset = 0;
	}
	Mouse::lastX = xpos;
	Mouse::lastY = ypos;

	InputManager::callOnMouseMoved(xpos, ypos, xOffset, yOffset);

	if (Mouse::leftButtonDown)
		InputManager::callOnMouseDragged(xpos, ypos, xOffset, yOffset);
}

void input_callback_cursorEnter(GLFWwindow* window, int entered) {
	if (entered)
		InputManager::callOnMouseEnter();
	else
		InputManager::callOnMouseLeave();
}

void input_callback_scroll(GLFWwindow* window, double xoffset, double yoffset) {
	InputManager::callOnScroll(xoffset, yoffset);
}

/***************************************************************************************************/
