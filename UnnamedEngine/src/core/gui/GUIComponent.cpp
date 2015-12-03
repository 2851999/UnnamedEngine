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

#include "../input/Input.h"
#include "GUIComponent.h"

/***************************************************************************************************
 * The GUIComponent class
 ***************************************************************************************************/

GUIComponent::GUIComponent(RenderableObject2D* object) {
	if (object != NULL)
		setSize(object->getSize());
	setup(object);
}

GUIComponent::GUIComponent(RenderableObject2D* object, float width, float height) {
	setSize(width, height);
	setup(object);
}

void GUIComponent::setup(GUIComponentRenderer* renderer) {
	this->renderer = renderer;
	setDefaults();
}

void GUIComponent::setup(RenderableObject2D* object) {
	this->renderer = new GUIComponentRenderer(object);
	setDefaults();
}

void GUIComponent::setDefaults() {
	name = "";
	visible = true;
	active = true;
	mouseHoveringInside = false;
	clicked = false;
	repeatClickedEvents = false;
	hasBeenClickedEvent = false;
	group = NULL;
	border = NULL;
	borderEnabled = false;
	positionPreference = GUIPosition::CENTRE;
	toolTip = NULL;
}

void GUIComponent::update() {
	if (visible && active) {
		if (getBounds().contains((float) Mouse::lastX, (float) Mouse::lastY)) {
			if (! mouseHoveringInside && ! Mouse::leftButtonDown) {
				mouseHoveringInside = true;
				callOnMouseEnterEvent();
			}
			if (Mouse::leftButtonDown && mouseHoveringInside) {
				if (repeatClickedEvents || (! repeatClickedEvents && ! hasBeenClickedEvent)) {
					clicked = true;
					hasBeenClickedEvent = true;
					callOnClickedEvent();
				}
			} else {
				clicked = false;
				hasBeenClickedEvent = false;
			}
		} else {
			if (mouseHoveringInside) {
				mouseHoveringInside = false;
				callOnMouseLeaveEvent();
			}
			clicked = false;
			hasBeenClickedEvent = false;
		}
		updateComponent();
		for (unsigned int a = 0; a < components.size(); a++)
			components[a]->update();
		if (toolTip != NULL)
			toolTip->update();
	}
}

void GUIComponent::render() {
	if (visible) {
		if (hasBorder() && borderEnabled)
			border->render();
		renderer->render(this, active);
		for (unsigned int a = 0; a < components.size(); a++)
			components[a]->render();
		renderComponent();
		if (toolTip != NULL)
			toolTip->render();
	}
}

void GUIComponent::renderText(std::string text) {
	Vector2f p = getPosition();
	renderer->font->render(text, p.getX(), p.getY());
}

void GUIComponent::renderText(std::string text, Vector2f offset) {
	Vector2f p = getPosition();
	renderer->font->render(text, p.getX() + offset.getX(), p.getY() + offset.getY());
}

void GUIComponent::callOnMouseEnterEvent() {
	componentOnMouseEnter();
	for (unsigned int a = 0; a < componentListeners.size(); a++)
		componentListeners[a]->onMouseEnter(this);
}

void GUIComponent::callOnMouseLeaveEvent() {
	componentOnMouseLeave();
	for (unsigned int a = 0; a < componentListeners.size(); a++)
		componentListeners[a]->onMouseLeave(this);
}

void GUIComponent::callOnClickedEvent() {
	componentOnClicked();
	for (unsigned int a = 0; a < componentListeners.size(); a++)
		componentListeners[a]->onClicked(this);
}

void GUIComponent::add(GUIComponent* component) {
	attach(component);
	components.push_back(component);
}

void GUIComponent::add(GUIComponent* component, GUIPosition pos, Vector2f offset) {
	component->positionPreference = pos;
	float xPos = 0;
	float yPos = 0;
	if (pos == GUIPosition::TOP) {
		std::vector<GUIComponent*> comps = getComponentsWithPositionPreference(pos);
		xPos = (getWidth() / 2) - (component->getWidth() / 2);
		yPos = 0;
		for (unsigned int a = 0; a < comps.size(); a++)
			yPos += comps[a]->getHeight();
	} else if (pos == GUIPosition::BOTTOM) {
		std::vector<GUIComponent*> comps = getComponentsWithPositionPreference(pos);
		xPos = (getWidth() / 2) - (component->getWidth() / 2);
		yPos = getHeight() - component->getHeight();
		for (unsigned int a = 0; a < comps.size(); a++)
			yPos -= comps[a]->getHeight();
	} else if (pos == GUIPosition::LEFT) {
		std::vector<GUIComponent*> comps = getComponentsWithPositionPreference(pos);
		xPos = 0;
		yPos = (getHeight() / 2) - (component->getHeight() / 2);
		for (unsigned int a = 0; a < comps.size(); a++)
			xPos += comps[a]->getWidth();
	} else if (pos == GUIPosition::RIGHT) {
		std::vector<GUIComponent*> comps = getComponentsWithPositionPreference(pos);
		xPos = getWidth() - component->getWidth();
		yPos = (getHeight() / 2) - (component->getHeight() / 2);
		for (unsigned int a = 0; a < comps.size(); a++)
			xPos -= comps[a]->getWidth();
	} else if (pos == GUIPosition::CENTRE) {
		xPos = (getWidth() / 2) - (component->getWidth() / 2);
		yPos = (getHeight() / 2) - (component->getHeight() / 2);
	}
	component->position = Vector2f(xPos, yPos) + offset;
	add(component);
}

std::vector<GUIComponent*> GUIComponent::getComponentsWithPositionPreference(GUIPosition preference) {
	std::vector<GUIComponent*> comps;
	for (unsigned int a = 0; a < components.size(); a++) {
		if (components[a]->positionPreference == preference)
			comps.push_back(components[a]);
	}
	return comps;
}

void GUIComponent::scale(Vector2f amount) {
	setScale(getScale() * amount);
	for (unsigned int a = 0; a < components.size(); a++)
		components[a]->scale(amount);
}

/***************************************************************************************************/

/***************************************************************************************************
 * The GUIGroup class
 ***************************************************************************************************/

GUIGroup::GUIGroup(std::string name) : GUIComponent(NULL) {
	this->name = name;
	setSize(0, 0);
}

void GUIGroup::updateComponent() {
	for (unsigned int a = 0; a < m_groupComponents.size(); a++)
		m_groupComponents[a]->update();
}

void GUIGroup::renderComponent() {
	for (unsigned int a = 0; a < m_groupComponents.size(); a++)
		m_groupComponents[a]->render();
}

void GUIGroup::add(GUIComponent* component) {
	component->setGroup(this);
	attach(component);
	m_groupComponents.push_back(component);
}

void GUIGroup::remove(GUIComponent* component) {
	for (unsigned int a = 0; a < m_groupComponents.size(); a++) {
		if (m_groupComponents[a] == component)
			m_groupComponents.erase(m_groupComponents.begin() + a);
	}
}

/***************************************************************************************************/

/***************************************************************************************************
 * The GUIBorder class
 ***************************************************************************************************/

GUIBorder::GUIBorder() {
	component = NULL;
	m_thickness = 0.0f;
	renderer = NULL;
}

GUIBorder::GUIBorder(GUIComponent* component, float thickness) {
	m_thickness = thickness;
	m_colours.push_back(Colour::WHITE);
	setup(component);
}

GUIBorder::GUIBorder(float thickness, Colour colour) {
	m_thickness = thickness;
	m_colours.push_back(colour);
	renderer = NULL;
	component = NULL;
}

GUIBorder::GUIBorder(float thickness, Texture* texture) {
	m_thickness = thickness;
	m_textures.push_back(texture);
	renderer = NULL;
	component = NULL;
}

GUIBorder::GUIBorder(GUIComponent* component, float thickness, Colour colour) {
	m_thickness = thickness;
	m_colours.push_back(colour);
	setup(component);
}

GUIBorder::GUIBorder(GUIComponent* component, float thickness, Texture* texture) {
	m_thickness = thickness;
	m_textures.push_back(texture);
	setup(component);
}

GUIBorder::GUIBorder(GUIComponent* component, float thickness, std::vector<Colour> colours) {
	m_thickness = thickness;
	m_colours = colours;
	setup(component);
}

GUIBorder::GUIBorder(GUIComponent* component, float thickness, std::vector<Texture*> textures) {
	m_thickness = thickness;
	m_textures = textures;
	setup(component);
}

void GUIBorder::setup(GUIComponent* component) {
	this->component = component;
	renderer = new GUIComponentRenderer(MeshBuilder::createQuad(component->getWidth() + (m_thickness * 2), component->getHeight() + (m_thickness * 2), Colour::WHITE));
	setPosition(-m_thickness, -m_thickness);
	this->component->attach(this);
	if (hasColour())
		renderer->colours = m_colours;
	if (hasTexture())
		renderer->textures = m_textures;
}

void GUIBorder::render() {
	if (renderer != NULL)
		renderer->render(this, component->active);
}

void GUIBorder::setColour(Colour colour) {
	m_colours.clear();
	m_colours.push_back(colour);
}

void GUIBorder::setTexture(Texture* texture) {
	m_textures.clear();
	m_textures.push_back(texture);
}

Colour GUIBorder::getColour() {
	if (m_colours.size() > 0)
		return m_colours[0];
	else
		return Colour::NONE;
}

Texture* GUIBorder::getTexture() {
	if (m_textures.size() > 0)
		return m_textures[0];
	else
		return NULL;
}

/***************************************************************************************************/

/***************************************************************************************************
 * The GUILabel class
 ***************************************************************************************************/

GUILabel::GUILabel(std::string text) : GUIComponent(NULL) {
	m_text = text;
	setWidth(renderer->font->getWidth(text));
	setHeight(renderer->font->getHeight(text));
}

GUILabel::GUILabel(std::string text, Font* font) : GUIComponent(NULL) {
	m_text = text;
	renderer->font = font;
	setWidth(font->getWidth(text));
	setHeight(font->getHeight(text));
}

void GUILabel::setText(std::string text) {
	m_text = text;
	setWidth(renderer->font->getWidth(text));
	setHeight(renderer->font->getHeight(text));
}

void GUILabel::setFont(Font* font) {
	renderer->font = font;
	setWidth(font->getWidth(m_text));
	setHeight(font->getHeight(m_text));
}

/***************************************************************************************************/

/***************************************************************************************************
 * The GUIToolTip class
 ***************************************************************************************************/

GUIToolTip::GUIToolTip(std::string text) {
	label = new GUILabel(text);
	label->border = new GUIBorder(label, 1.0f, Colour::LIGHT_GREY);
	label->borderEnabled = true;
	timer = new Timer();
	time = 1000;
	showing = false;
	component = NULL;
}

GUIToolTip::GUIToolTip(GUIComponent* component, std::string text) : GUIToolTip(text) {
	setComponent(component);
}

GUIToolTip::GUIToolTip(std::string text, Colour colour) {
	label = new GUILabel(text);
	label->border = new GUIBorder(label, 1.0f, colour);
	label->borderEnabled = true;
	timer = new Timer();
	time = 1000;
	showing = false;
	component = NULL;
}

GUIToolTip::GUIToolTip(GUIComponent* component, std::string text, Colour colour) : GUIToolTip(text, colour) {
	setComponent(component);
}

void GUIToolTip::setComponent(GUIComponent* component) {
	component->addListener(this);
	this->component = component;
}

void GUIToolTip::update() {
	if (timer->hasTimePassed(time)) {
		label->setPosition((float) Mouse::lastX, (float) Mouse::lastY);
		showing = true;
		timer->reset();
	}
}

void GUIToolTip::render() {
	if (showing)
		label->render();
}

void GUIToolTip::onMouseEnter(GUIComponent* component) {
	if (this->component == component)
		timer->start();
}

void GUIToolTip::onMouseLeave(GUIComponent* component) {
	if (this->component == component) {
		timer->reset();
		showing = false;
	}
}

void GUIToolTip::onClicked(GUIComponent* component) {
	if (this->component == component) {
		timer->reset();
		showing = false;
	}
}

/***************************************************************************************************/

/***************************************************************************************************
 * The GUIFill class
 ***************************************************************************************************/

void GUIFill::setup(GUIComponent* component) {
	this->component = component;
	this->component->attach(this);
	if (texture != NULL)
		renderer = new GUIComponentRenderer(MeshBuilder::createQuad(component->getWidth(), component->getHeight(), texture, Colour::WHITE));
	else
		renderer = new GUIComponentRenderer(MeshBuilder::createQuad(component->getWidth(), component->getHeight(), Colour::WHITE));
	colour = Colour::WHITE;
}

void GUIFill::update() {
	if (renderer != NULL) {
		renderer->colours.clear();
		renderer->colours.push_back(colour);
		if (texture != NULL) {
			renderer->textures.clear();
			renderer->textures.push_back(texture);
		}
		if (size.getX() != lastWidth || size.getY() != lastHeight) {
			renderer->entity->getMesh()->getData()->clearPositions();
			MeshBuilder::addQuadV(renderer->entity->getMesh()->getData(), Vector2f(0, 0), Vector2f(size.getX(), size.getY()));
			renderer->entity->getMesh()->updateVertices();
			lastWidth = size.getX();
			lastHeight = size.getY();
		}
	}
}

void GUIFill::render() {
	renderer->render(this, component->active);
}

/***************************************************************************************************/
