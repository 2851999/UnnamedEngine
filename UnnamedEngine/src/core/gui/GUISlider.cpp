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

#include "GUISlider.h"

/***************************************************************************************************
 * The GUISlider class
 ***************************************************************************************************/

void GUISlider::updateComponent() {
	sliderButton->update();
}

void GUISlider::renderComponent() {
	float width = getWidth();
	float height = getHeight();
	float buttonWidth = sliderButton->getWidth();
	float buttonHeight = sliderButton->getHeight();

	//Check the slider direction
	if (sliderDirection == DIRECTION_VERTICAL) {
		//Clamp the boundaries
		if (sliderButton->position.getY() < 0)
			sliderButton->position.setY(0);
		else if (sliderButton->position.getY() > height - buttonHeight)
			sliderButton->position.setY(height - buttonHeight);
		//Make sure the button is in the middle
		sliderButton->position.setX(-buttonWidth / 2 + width / 2);
	} else if (sliderDirection == DIRECTION_HORIZONTAL) {
		//Clamp the boundaries
		if (sliderButton->position.getX() < 0)
			sliderButton->position.setX(0);
		else if (sliderButton->position.getX() > width - buttonWidth)
			sliderButton->position.setX(width - buttonWidth);
		//Make sure the button is in the middle
		sliderButton->position.setY(-buttonHeight / 2 + height / 2);
	}
	//Render the button
	sliderButton->render();
}

void GUISlider::onMouseDragged(double x, double y, double dx, double dy) {
	//Make sure this is visible and active
	if (visible && active) {
		float width = getWidth();
		float height = getHeight();
		//Get this sider's position
		Vector2f p = getPosition();
		//Check the direction of this slider
		if (sliderDirection == DIRECTION_VERTICAL) {
			if (sliderButton->mouseHoveringInside) {
				if (y > p.getY() && y < p.getY() + height) {
					sliderButton->position.setY(sliderButton->position.getY() + dy);
					//Set the slider value
					sliderValue = (sliderButton->position.getY() / (height - sliderButton->getHeight())) * 100;
				}
			}
		} else if (sliderDirection == DIRECTION_HORIZONTAL) {
			if (sliderButton->mouseHoveringInside) {
				if (x > p.getX() && x < p.getX() + width) {
					sliderButton->position.setX(sliderButton->position.getX() + dx);
					//Set the slider value
					sliderValue = (sliderButton->position.getX() / (height - sliderButton->getWidth())) * 100;
				}
			}
		}
		//Clamp the slider value
		if (sliderValue < 0)
			sliderValue = 0;
		else if (sliderValue > 100)
			sliderValue = 100;
	}
}

void GUISlider::setColour(Colour colour) {
	renderer->colours.clear();
	renderer->colours.push_back(colour);
}

void GUISlider::setTexture(Texture* texture) {
	renderer->textures.clear();
	renderer->textures.push_back(texture);
}

/***************************************************************************************************/
