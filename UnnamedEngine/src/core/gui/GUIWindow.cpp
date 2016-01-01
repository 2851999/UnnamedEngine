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

#include "GUIWindow.h"
#include "../Game.h"

/***************************************************************************************************
 * The GUIWindow class
 ***************************************************************************************************/

void GUIWindow::centre() {
	setPosition((Game::current->getSettings()->getWindowWidth() / 2) - (getWidth() / 2), (Game::current->getSettings()->getWindowHeight() / 2) - (getHeight() / 2));
}

void GUIWindow::updateComponent() {
	topBar->update();
	if (closeButton != NULL) {
		closeButton->update();
		if (closeButton->clicked)
			close();
	}
}

void GUIWindow::renderComponent() {
	topBar->render();
	renderTextAtCentre(title, Vector2f(0, -(getHeight() / 2 - topBar->getHeight() / 2)));
	if (closeButton != NULL)
		closeButton->render();
}

void GUIWindow::close() {
	visible = false;
	active = false;
}

void GUIWindow::onMousePressed(int button) {
	if (visible && active) {
		if (topBar->getBounds().contains((float) Mouse::lastX, (float) Mouse::lastY))
			m_mousePressed = true;
	}
}

void GUIWindow::onMouseReleased(int button) {
	if (visible && active)
		m_mousePressed = false;
}

void GUIWindow::onMouseDragged(double x, double y, double dx, double dy) {
	if (visible && active) {
		if (this->topBar->getBounds().contains((float) (x - dx), (float) (y - dy)) && m_mousePressed)
			position += Vector2f(dx, dy);
	}
}

void GUIWindow::setColour(Colour colour) {
	renderer->colours.clear();
	renderer->colours.push_back(colour);
}

void GUIWindow::setTexture(Texture* texture) {
	renderer->textures.clear();
	renderer->textures.push_back(texture);
}

void GUIWindow::setBarColour(Colour colour) {
	topBar->colour = colour;
}

void GUIWindow::setBarTexture(Texture* texture) {
	topBar->texture = texture;
}

void GUIWindow::setCloseButton(GUIButton* closeButton) {
	this->closeButton = closeButton;
	closeButton->position = Vector2f(getWidth() - closeButton->getWidth(), 0);
	attach(closeButton);
}

/***************************************************************************************************/
