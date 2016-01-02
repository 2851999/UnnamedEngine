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

#include <GL/GLEW/glew.h>
#include <GL/GLFW/glfw3.h>

#include "../../utils/StringUtils.h"
#include "Input.h"
#include "Controller.h"

/***************************************************************************************************
 * The Controller class
 ***************************************************************************************************/

void Controller::setup() {
	int numButtons = 0;
	int numAxes = 0;

	glfwGetJoystickButtons(m_index, &numButtons);
	glfwGetJoystickAxes(m_index, &numAxes);

	for (int a = 0; a < numButtons; a++)
		m_buttons.push_back(new ControllerButton(this, a));
	for (int a = 0; a < numAxes; a++)
		m_axes.push_back(new ControllerAxis(this, a));
}

void Controller::checkInput() {
	for (unsigned int a = 0; a < m_buttons.size(); a++)
		m_buttons.at(a)->checkInput();
	for (unsigned int a = 0; a < m_axes.size(); a++)
		m_axes.at(a)->checkInput();
}

std::string Controller::getName() {
	return to_string(glfwGetJoystickName(m_index));
}

bool Controller::isPresent(unsigned int index) {
	return glfwJoystickPresent(index) == GL_TRUE;
}

std::vector<unsigned int> Controller::getAvailableControllerIndices() {
	std::vector<unsigned int> available;
	for (unsigned int a = GLFW_JOYSTICK_1; a < GLFW_JOYSTICK_LAST; a++) {
		if (isPresent(a))
			available.push_back(a);
	}
	return available;
}

/***************************************************************************************************/

/***************************************************************************************************
 * The ControllerButton class
 ***************************************************************************************************/

void ControllerButton::checkInput() {
	int numButtons;
	if ((glfwGetJoystickButtons(m_controller->getIndex(), &numButtons)[m_index] == GLFW_PRESS) != m_pressed) {
		m_pressed = ! m_pressed;

		if (m_pressed)
			InputManager::callOnControllerButtonPressed(this);
		else
			InputManager::callOnControllerButtonReleased(this);
	}
}

/***************************************************************************************************/

/***************************************************************************************************
 * The ControllerAxis class
 ***************************************************************************************************/

void ControllerAxis::checkInput() {
	int numAxes;
	float currentValue = glfwGetJoystickAxes(m_controller->getIndex(), &numAxes)[m_index];
	if (m_value != currentValue) {
		m_value = currentValue;
		InputManager::callOnControllerAxisChange(this);
	}
}

/***************************************************************************************************/
