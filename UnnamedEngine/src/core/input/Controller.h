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

#ifndef CORE_INPUT_CONTROLLER_H_
#define CORE_INPUT_CONTROLLER_H_

#include <vector>
#include <string>

class ControllerButton;
class ControllerAxis;

/***************************************************************************************************
 * The Controller class
 ***************************************************************************************************/

class Controller {
private:
	unsigned int m_index;

	/* The buttons and axes */
	std::vector<ControllerButton*> m_buttons;
	std::vector<ControllerAxis*>   m_axes;
public:
	/* The constructor */
	Controller(unsigned int index) : m_index(index) {
		setup();
	}

	/* The method used to setup this controller */
	void setup();

	/* The method used to check for changes in this controller */
	void checkInput();

	/* The setters and getters */
	inline unsigned int getIndex() { return m_index; }
	std::string getName();
	inline std::vector<ControllerButton*> getButtons() { return m_buttons; }
	inline std::vector<ControllerAxis*> getAxes() { return m_axes; }
	inline unsigned int getNumButtons() { return m_buttons.size(); }
	inline unsigned int getNumAxes() { return m_axes.size(); }
	inline ControllerButton* getButton(unsigned int index) { return m_buttons.at(index); }
	inline ControllerAxis* getAxes(unsigned int index) { return m_axes.at(index); }

	/* Some static utility methods */

	/* Checks whether a joystick is present */
	static bool isPresent(unsigned int index);

	/* Returns a vector containing all of the index's for available controllers */
	static std::vector<unsigned int> getAvailableControllerIndices();
};

/***************************************************************************************************/

/***************************************************************************************************
 * The ControllerButton class
 ***************************************************************************************************/

class ControllerButton {
private:
	/* The controller this button belongs to */
	Controller* m_controller = NULL;

	/* The index of this button */
	unsigned int m_index;

	/* The current state of this button */
	bool m_pressed = false;
public:
	/* The constructor */
	ControllerButton(Controller* controller, unsigned int index) : m_controller(controller), m_index(index) {}

	/* The method used to check the state of this button */
	void checkInput();

	inline bool operator==(ControllerButton* other) {
		return (getIndex() == other->getIndex()) && (getController()->getIndex() == other->getController()->getIndex());
	}

	/* The setters and getters */
	inline Controller* getController() { return m_controller; }
	inline unsigned int getIndex() { return m_index; }
	inline bool isPressed() { return m_pressed; }
};

/***************************************************************************************************/

/***************************************************************************************************
 * The ControllerAxis class
 ***************************************************************************************************/

class ControllerAxis {
private:
	/* The controller this axis belongs to */
	Controller* m_controller = NULL;

	/* The index of this axis */
	unsigned int m_index;

	/* The current value of this axis */
	float m_value = 0;
public:
	/* The constructor */
	ControllerAxis(Controller* controller, unsigned int index) : m_controller(controller), m_index(index) {}

	/* The method used to check the state of this axis */
	void checkInput();

	inline bool operator==(ControllerAxis* other) {
		return (getIndex() == other->getIndex()) && (getController()->getIndex() == other->getController()->getIndex());
	}

	/* The setters and getters */
	inline Controller* getController() { return m_controller; }
	inline unsigned int getIndex() { return m_index; }
	inline float getValue() { return m_value; }
};

/***************************************************************************************************/

#endif /* CORE_INPUT_CONTROLLER_H_ */
