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

#include "GUILoadingBar.h"

/***************************************************************************************************
 * The GUILoadingBar class
 ***************************************************************************************************/

void GUILoadingBar::renderComponent() {
	barFill->render();
}

void GUILoadingBar::completedStage() {
	if (currentLoadingStage != loadingStages) {
		currentLoadingStage ++;
		barFill->setWidth((getWidth() / loadingStages) * currentLoadingStage);
		barFill->setHeight(getHeight());
		barFill->update();
		stageChanged();
	}
}

void GUILoadingBar::setCurrentStage(unsigned int stage) {
	if (stage <= loadingStages) {
		currentLoadingStage = stage;
		barFill->setWidth((getWidth() / loadingStages) * currentLoadingStage);
		barFill->setHeight(getHeight());
		barFill->update();
	}
}

void GUILoadingBar::setBackgroundColour(Colour colour) {
	renderer->colours.clear();
	renderer->colours.push_back(colour);
}

Colour GUILoadingBar::getBackgroundColour() {
	if (renderer->colours.size() > 0)
		return renderer->colours[0];
	else
		return Colour::NONE;
}

void GUILoadingBar::setBackgroundTexture(Texture* texture) {
	renderer->textures.clear();
	renderer->textures.push_back(texture);
}

Texture* GUILoadingBar::getBackgroundTexture() {
	if (renderer->textures.size() > 0)
		return renderer->textures[0];
	else
		return NULL;
}

void GUILoadingBar::setFillColour(Colour colour) {
	barFill->colour = colour;
}

Colour GUILoadingBar::getFillColour() {
	return barFill->colour;
}

void GUILoadingBar::setFillTexture(Texture* texture) {
	barFill->texture = texture;
}

Texture* GUILoadingBar::getFillTexture() {
	return barFill->texture;
}

/***************************************************************************************************/
