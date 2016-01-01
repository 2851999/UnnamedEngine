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

#ifndef CORE_GUI_GUISLIDER_H_
#define CORE_GUI_GUISLIDER_H_

#include "../input/Input.h"
#include "GUIButton.h"

/***************************************************************************************************
 * The GUISlider class
 ***************************************************************************************************/

class GUISlider : public GUIComponent, InputListener {
public:
	/* The slider direction */
	static const unsigned int DIRECTION_HORIZONTAL = 1;
	static const unsigned int DIRECTION_VERTICAL   = 2;

	/* This slider's direction */
	unsigned int sliderDirection = 0;

	/* The slider button */
	GUIButton* sliderButton = NULL;

	/* The current slider value */
	float sliderValue = 0;

	/* The various constructors */
	GUISlider(GUIButton* button, int direction, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, Colour::WHITE), width, height)) {

		sliderButton = button;
		sliderDirection = direction;
		renderer->colours.push_back(Colour::WHITE);
		attach(sliderButton);
		InputListener::addListener();
	}

	GUISlider(GUIButton* button, Colour colour, int direction, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, Colour::WHITE), width, height)) {

		sliderButton = button;
		sliderDirection = direction;
		renderer->colours.push_back(colour);
		attach(sliderButton);
		InputListener::addListener();
	}

	GUISlider(GUIButton* button, Texture* texture, int direction, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, Colour::WHITE), width, height)) {

		sliderButton = button;
		sliderDirection = direction;
		renderer->colours.push_back(Colour::WHITE);
		renderer->textures.push_back(texture);
		attach(sliderButton);
		InputListener::addListener();
	}

	GUISlider(GUIButton* button, Texture* texture, Colour colour, int direction, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, Colour::WHITE), width, height)) {

		sliderButton = button;
		sliderDirection = direction;
		renderer->colours.push_back(colour);
		renderer->textures.push_back(texture);
		attach(sliderButton);
		InputListener::addListener();
	}

	/* The update and render methods */
	void updateComponent() override;
	void renderComponent() override;

	/* The input methods needed */
	virtual void onMouseDragged(double x, double y, double dx, double dy) override;

	/* The setters and getters */
	void setColour(Colour colour);
	void setTexture(Texture* texture);
	inline Colour getColour() { return renderer->colours.at(0); }
	inline Texture* getTexture() { return renderer->textures.at(0); }
	inline bool hasColour() { return renderer->colours.size() > 0; }
	inline bool hasTexture() { return renderer->textures.size() > 0; }
};

/***************************************************************************************************/

#endif /* CORE_GUI_GUISLIDER_H_ */
