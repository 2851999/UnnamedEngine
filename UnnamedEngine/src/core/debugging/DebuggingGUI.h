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

#ifndef CORE_DEBUGGING_DEBUGGINGGUI_H_
#define CORE_DEBUGGING_DEBUGGINGGUI_H_

#include "../input/Input.h"

#include "../gui/GUIPanel.h"
#include "../gui/GUITextBox.h"

/***************************************************************************************************
 * The DebuggingGUI class
 ***************************************************************************************************/

class DebuggingGUI : public GUIPanel, public InputListener {
private:
	GUITextBox* m_commandTextBox = NULL;
public:
	DebuggingGUI(int width, int height) : GUIPanel("DebuggingGUI", false) {
		//Create all of the components

		m_commandTextBox = new GUITextBox(Colour(Colour::BLACK, 0.75f), width, 20);
		m_commandTextBox->renderer->font = Font::loadFont("resources/textures/font-segoeui.png", 16, 18);
		m_commandTextBox->setPosition(0, height - m_commandTextBox->getHeight());
		m_commandTextBox->setDefaultText("Enter something");
		m_commandTextBox->selection->setColour(Colour(Colour::WHITE, 0.25f));
		m_commandTextBox->cursor->setColour(Colour(Colour::WHITE, 0.25f));

		//Add all of the components
		add(m_commandTextBox);

		InputListener::addListener();
	}

	void processCommand(std::string command) {
		std::vector<std::string> split = split_string(command, ' ');

		if (split[0] == "print") {
			for (unsigned int n = 1; n < split.size(); n++) {
				std::cout << split[n];
				if (n != split.size() - 1)
					std::cout << " ";
			}
			std::cout << std::endl;
		}
	}

	void onKeyPressed(int code) override {}
	void onKeyReleased(int code) override {}
	void onKeyTyped(int code) override {
		if (code == GLFW_KEY_F1) {
			m_commandTextBox->setSelected(true);

			Mouse::unlock();
		} else if (code == GLFW_KEY_ENTER && m_commandTextBox->isSelected()) {
			m_commandTextBox->setSelected(false);
			processCommand(m_commandTextBox->getText());
			m_commandTextBox->clear();

			Mouse::lock();
		}
	}
	void onChar(int code, char character) override {}

	void onMousePressed(int button) override {}
	void onMouseReleased(int button) override {}
	void onMouseClicked(int button) override {}
	void onMouseMoved(double x, double y, double dx, double dy) override {}
	void onMouseDragged(double x, double y, double dx, double dy) override {}
	void onMouseEnter() override {}
	void onMouseLeave() override {}

	void onScroll(double dx, double dy) override {}

	void onControllerButtonPressed(ControllerButton* button) override {}
	void onControllerButtonReleased(ControllerButton* button) override {}
	void onControllerAxisChange(ControllerAxis* axis) override {}
};

/***************************************************************************************************/

#endif /* CORE_DEBUGGING_DEBUGGINGGUI_H_ */
