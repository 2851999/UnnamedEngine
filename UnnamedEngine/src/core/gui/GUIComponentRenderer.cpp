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

#include "GUIComponentRenderer.h"

/***************************************************************************************************
 * The GUIComponentRenderer
 ***************************************************************************************************/

Font* GUIComponentRenderer::defaultFont;

GUIComponentRenderer::GUIComponentRenderer(RenderableObject2D* entity) {
	this->entity = entity;
	this->font = defaultFont;

	this->inactiveColour = Colour(-1, -1, -1, -1);
	this->inactiveTexture = NULL;
	this->componentIndex = 0;
}

void GUIComponentRenderer::render(Object2D* object, bool active) {
	if (entity != NULL) {
		entity->setPosition(object->getPosition());
		entity->setRotation(object->getRotation());
		entity->setScale(object->getScale());
		entity->setWidth(object->getWidth());
		entity->setHeight(object->getHeight());

		entity->update();

		if (active || (! shouldUseInactiveTexture()) || (! shouldUseInactiveColour())) {
			if (shouldUseTextures()) {
				entity->getMesh()->getData()->clearTextureCoords();
				MeshBuilder::addQuadT(entity->getMesh()->getData(), textures[componentIndex]);
				entity->getMesh()->updateTextureCoords();
				entity->getMesh()->setTexture(textures[componentIndex]);

				if (shouldUseColours()) {
					entity->getMesh()->getData()->clearColours();
					MeshBuilder::addQuadC(entity->getMesh()->getData(), colours[componentIndex]);
					entity->getMesh()->updateColours();
				} else {
					entity->getMesh()->getData()->clearColours();
					MeshBuilder::addQuadC(entity->getMesh()->getData(), Colour::WHITE);
					entity->getMesh()->updateColours();
				}
			} else if (shouldUseColours()) {
				entity->getMesh()->getData()->clearColours();
				MeshBuilder::addQuadC(entity->getMesh()->getData(), colours[componentIndex]);
				entity->getMesh()->updateColours();
			}
		} else {
			if (shouldUseInactiveTexture()) {
				entity->getMesh()->setTexture(inactiveTexture);
				if (shouldUseInactiveColour()) {
					entity->getMesh()->getData()->clearColours();
					MeshBuilder::addQuadC(entity->getMesh()->getData(), inactiveColour);
					entity->getMesh()->updateColours();
				}
			} else if (shouldUseInactiveColour())  {
				entity->getMesh()->getData()->clearColours();
				MeshBuilder::addQuadC(entity->getMesh()->getData(), inactiveColour);
				entity->getMesh()->updateColours();
			}
		}
		entity->render();
	}
}

int GUIComponentRenderer::getTotalComponents() {
	if (shouldUseTextures())
		return textures.size();
	else if (shouldUseColours())
		return colours.size();
	else
		return 0;
}

/***************************************************************************************************/
