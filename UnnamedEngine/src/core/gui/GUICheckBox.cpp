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

#include "../Object.h"
#include "GUICheckBox.h"

/***************************************************************************************************
 * The GUICheckBox class
 ***************************************************************************************************/

GUICheckBox::GUICheckBox(GUIComponentRenderer* renderer) {
	setup(renderer);
	checked = false;
}

GUICheckBox::GUICheckBox(std::vector<Colour> colours, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, Colour::WHITE), width, height)) {
	this->renderer->colours = colours;
	checked = false;
}

GUICheckBox::GUICheckBox(std::vector<Texture*> textures, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, textures[0], Colour::WHITE), width, height)) {
	this->renderer->textures = textures;
	checked = false;
}

GUICheckBox::GUICheckBox(std::vector<Texture*> textures, std::vector<Colour> colours, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, textures[0], Colour::WHITE), width, height)) {
	this->renderer->colours = colours;
	this->renderer->textures = textures;
	checked = false;
}

GUICheckBox::GUICheckBox(std::string text, std::vector<Colour> colours, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, Colour::WHITE), width, height)) {
	this->renderer->colours = colours;
	this->text = text;
	checked = false;
}

GUICheckBox::GUICheckBox(std::string text, std::vector<Texture*> textures, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, textures[0], Colour::WHITE), width, height)) {
	this->renderer->textures = textures;
	this->text = text;
	checked = false;
}

GUICheckBox::GUICheckBox(std::string text, std::vector<Texture*> textures, std::vector<Colour> colours, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, textures[0], Colour::WHITE), width, height)) {
	this->renderer->colours = colours;
	this->renderer->textures = textures;
	this->text = text;
	checked = false;
}

void GUICheckBox::updateComponent() {
	int components = renderer->getTotalComponents();
	if (checked) {
		if (components == 1)
			renderer->componentIndex = 0;
		else if (components == 2)
			renderer->componentIndex = 1;
		else if (components == 3)
			renderer->componentIndex = 2;
	} else if (mouseHoveringInside) {
		if (components == 1)
			renderer->componentIndex = 0;
		else if (components == 2)
			renderer->componentIndex = 1;
		else if (components == 3)
			renderer->componentIndex = 1;
	} else {
		if (components == 1)
			renderer->componentIndex = 0;
		else if (components == 2)
			renderer->componentIndex = 0;
		else if (components == 3)
			renderer->componentIndex = 0;
	}
}

/***************************************************************************************************/
