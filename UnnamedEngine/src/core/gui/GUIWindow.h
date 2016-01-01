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

#ifndef CORE_GUI_GUIWINDOW_H_
#define CORE_GUI_GUIWINDOW_H_

#include "../input/Input.h"
#include "GUIButton.h"

/***************************************************************************************************
 * The GUIWindow class
 ***************************************************************************************************/

class GUIWindow : public GUIComponent, InputListener {
private:
	/* Whether the mouse is currently pressed within the top bar */
	bool m_mousePressed = false;
public:
	/* The window's title */
	std::string title;

	/* The top bar */
	GUIFill* topBar = NULL;

	/* The close button */
	GUIButton* closeButton = NULL;

	/* The constructors */
	GUIWindow(std::string title, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, Colour::WHITE), width, height)) {
		this->title = title;
		renderer->colours.push_back(Colour::WHITE);
		topBar = new GUIFill(this);
		topBar->setSize(getWidth(), 20);
		InputListener::addListener();
	}

	GUIWindow(std::string title, Colour colour, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, Colour::WHITE), width, height)) {
		this->title = title;
		renderer->colours.push_back(colour);
		topBar = new GUIFill(this);
		topBar->setSize(getWidth(), 20);
		InputListener::addListener();
	}

	GUIWindow(std::string title, Texture* texture, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, Colour::WHITE), width, height)) {
		this->title = title;
		renderer->colours.push_back(Colour::WHITE);
		renderer->textures.push_back(texture);
		topBar = new GUIFill(this);
		topBar->setSize(getWidth(), 20);
		InputListener::addListener();
	}

	GUIWindow(std::string title, Colour colour, Texture* texture, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, Colour::WHITE), width, height)) {
		this->title = title;
		renderer->colours.push_back(colour);
		renderer->textures.push_back(texture);
		topBar = new GUIFill(this);
		topBar->setSize(getWidth(), 20);
		InputListener::addListener();
	}

	void centre();

	/* The update and render methods */
	void updateComponent() override;
	void renderComponent() override;

	void close();

	virtual void onMousePressed(int button) override;
	virtual void onMouseReleased(int button) override;
	virtual void onMouseDragged(double x, double y, double dx, double dy) override;

	/* The setters and getters */
	void setColour(Colour colour);
	void setTexture(Texture* texture);
	inline Colour getColour() { return renderer->colours.at(0); }
	inline Texture* getTexture() { return renderer->textures.at(0); }
	inline bool hasColour() { return renderer->colours.size() > 0; }
	inline bool hasTexture() { return renderer->textures.size() > 0; }

	void setBarColour(Colour colour);
	void setBarTexture(Texture* texture);
	inline Colour getBarColour() { return topBar->colour; }
	inline Texture* getBarTexture() { return topBar->texture; }
	inline bool hasBarColour() { return topBar->colour.getA() != -1; }
	inline bool hasBarTexture() { return topBar->texture != NULL; }

	void setCloseButton(GUIButton* closeButton);
};

/***************************************************************************************************/

#endif /* CORE_GUI_GUIWINDOW_H_ */
