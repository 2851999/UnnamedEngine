/*****************************************************************************
 *
 *   Copyright 2015 Joel Davies
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

#include "GUIDropDownMenu.h"

/***************************************************************************************************
 * The GUIDropDownMenu class
 ***************************************************************************************************/

GUIDropDownMenu::GUIDropDownMenu(GUIButton* button) : GUIComponent(NULL) {
	menuButton = button;
	if (menuButton != NULL) {
		setSize(menuButton->getSize());
		menuButton->addListener(this);
	}
	menuOpen = false;
	InputListener::addListener();
}

void GUIDropDownMenu::updateComponent() {
	updateMenu();
}

void GUIDropDownMenu::renderComponent() {
	if (menuButton != NULL)
		menuButton->render();
	if (menuOpen) {
		for (unsigned int a = 0; a < buttons.size(); a++)
			buttons[a]->render();
	}
}

void GUIDropDownMenu::updateMenu() {
	menuButton->update();
	menuButton->visible = visible;
	menuButton->active = active;
	menuButton->setPosition(position);
	borderEnabled = menuOpen;

	float currentY = position.getY() + menuButton->getHeight();
	for (unsigned int a = 0; a < buttons.size(); a++) {
		buttons[a]->visible = visible && menuOpen;
		buttons[a]->active = active && menuOpen;
		buttons[a]->setPosition(Vector2f(position.getX(), currentY));
		buttons[a]->update();
		currentY += buttons[a]->getHeight();
	}
}

void GUIDropDownMenu::onClicked(GUIComponent* component) {
	menuOpen = ! menuOpen;
}

void GUIDropDownMenu::onMouseClicked(int button) {
	if (menuOpen && (! getMenuBounds().contains((float) Mouse::lastX, (float) Mouse::lastY)))
		menuOpen = false;
}

void GUIDropDownMenu::addButton(GUIButton* button) {
	button->addListener(this);
	buttons.push_back(button);
	Rect bounds = getMenuBounds();
	setSize(bounds.width, bounds.height);
}

void GUIDropDownMenu::addButton(GUIButton* button, std::string name) {
	button->setName(name);
	addButton(button);
}

Rect GUIDropDownMenu::getMenuBounds() {
	Vector2f position = getPosition();
	float x = position.getX();
	float y = position.getY();
	float width = menuButton->getWidth();
	float height = menuButton->getHeight();

	for (unsigned int a = 0; a < buttons.size(); a++) {
		height += buttons[a]->getHeight();
		if (buttons[a]->getWidth() > width)
			width = buttons[a]->getWidth();
	}
	return Rect(x, y, width, height);
}

/***************************************************************************************************/
