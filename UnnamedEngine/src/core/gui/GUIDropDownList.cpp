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

#include "GUIDropDownList.h"

/***************************************************************************************************
 * The GUIDropDownList class
 ***************************************************************************************************/

GUIDropDownList::GUIDropDownList(GUIButton* menuButton) :
	GUIDropDownMenu(menuButton) {
	overlay = NULL;
	overlayTexture = NULL;
}

GUIDropDownList::GUIDropDownList(GUIButton* menuButton, Texture* overlayTexture) :
	GUIDropDownMenu(menuButton) {
	setupOverlay(overlayTexture);
}

void GUIDropDownList::setupOverlay(Texture* texture) {
	overlayTexture = texture;
	overlay = new RenderableObject2D(MeshBuilder::createQuad(menuButton->getWidth(), menuButton->getHeight(), overlayTexture, Colour::WHITE));
}

void GUIDropDownList::renderComponent() {
	if (menuButton != NULL)
		menuButton->render();
	if (overlay != NULL) {
		overlay->position = menuButton->position;
		overlay->render();
	}
	if (menuOpen) {
		for (unsigned int a = 0; a < buttons.size(); a++)
			buttons[a]->render();
	}
}

void GUIDropDownList::onClicked(GUIComponent* component) {
	if (component != menuButton) {
		menuOpen = false;
		buttons.push_back(menuButton);
		GUIButton* newMenuButton = NULL;
		for (unsigned int a = 0; a < buttons.size(); a++) {
			if (buttons[a] == component) {
				newMenuButton = buttons[a];

				buttons.erase(buttons.begin() + a);
				break;
			}
		}
		menuButton = newMenuButton;
		menuButton->clicked = false;
		menuButton->mouseHoveringInside = false;
		updateMenu();
	} else {
		menuOpen = ! menuOpen;
	}
}

/***************************************************************************************************/
