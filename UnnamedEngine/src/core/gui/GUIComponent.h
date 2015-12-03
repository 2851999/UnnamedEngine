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

#ifndef CORE_GUI_GUICOMPONENT_H_
#define CORE_GUI_GUICOMPONENT_H_

#include <string>

#include "../../utils/Timer.h"
#include "GUIComponentRenderer.h"

/***************************************************************************************************
 * The GUIPosition enum
 ***************************************************************************************************/

enum GUIPosition {
	TOP, BOTTOM, LEFT, RIGHT, CENTRE, NONE
};

/***************************************************************************************************/

/***************************************************************************************************
 * The GUIComponentListener class
 ***************************************************************************************************/

class GUIComponent;

class GUIComponentListener {
public:
	GUIComponentListener() {}
	virtual ~GUIComponentListener() {}
	virtual void onMouseEnter(GUIComponent* component) {}
	virtual void onMouseLeave(GUIComponent* component) {}
	virtual void onClicked(GUIComponent* component) {}
};

/***************************************************************************************************/

class GUIGroup;
class GUIBorder;
class GUIToolTip;

/***************************************************************************************************
 * The GUIComponent class
 ***************************************************************************************************/

class GUIComponent : public Object2D {
protected:
	virtual void updateComponent() {}
	virtual void renderComponent() {}
	virtual void componentOnMouseEnter() {}
	virtual void componentOnMouseLeave() {}
	virtual void componentOnClicked() {}
public:
	GUIComponentRenderer* renderer;
	std::string name;
	bool visible;
	bool active;
	bool mouseHoveringInside;
	bool clicked;
	bool repeatClickedEvents;
	bool hasBeenClickedEvent;
	std::vector<GUIComponentListener*> componentListeners;
	GUIGroup* group;
	GUIBorder* border;
	bool borderEnabled;
	std::vector<GUIComponent*> components;
	GUIPosition positionPreference;
	GUIToolTip* toolTip;

	GUIComponent() {
		renderer = NULL;
		setDefaults();
	}

	GUIComponent(RenderableObject2D* object);
	GUIComponent(RenderableObject2D* object, float width, float height);

	virtual ~GUIComponent() {}

	void setup(GUIComponentRenderer* renderer);
	void setup(RenderableObject2D* object);
	void setDefaults();

	void update();
	void render();

	void renderText(std::string text);
	void renderText(std::string text, Vector2f offset);
	inline void renderText(std::string text, float x, float y) { renderer->font->render(text, x, y); }
	inline void renderTextAtCentre(std::string text) { renderer->font->renderAtCentre(text, this, Vector2f(0, 0)); }
	inline void renderTextAtCentre(std::string text, Vector2f offset) { renderer->font->renderAtCentre(text, this, offset); }
	inline void addListener(GUIComponentListener* listener) { componentListeners.push_back(listener); }
	void callOnMouseEnterEvent();
	void callOnMouseLeaveEvent();
	void callOnClickedEvent();
	void add(GUIComponent* component);
	void add(GUIComponent* component, GUIPosition pos, Vector2f offset);
	inline void add(GUIComponent* component, GUIPosition pos) { add(component, pos, Vector2f(0, 0)); }

	std::vector<GUIComponent*> getComponentsWithPositionPreference(GUIPosition preference);
	void scale(Vector2f amount);

	inline void setName(std::string name) { this->name = name; }
	inline void setVisible(bool visible) { this->visible = visible; }
	inline void setActive(bool active) { this->active = active; }
	inline void setRepeatClickedEvents(bool repeatClickedEvents) { this->repeatClickedEvents = repeatClickedEvents; }
	inline void setGroup(GUIGroup* group) { this->group = group; }
	inline void setBorder(GUIBorder* border) { this->border = border; }
	inline void setBorderEnabled(bool borderEnabled) { this->borderEnabled = borderEnabled; }
	inline void setComponents(std::vector<GUIComponent*> components) { this->components = components; }
	inline void setPositionPreference(GUIPosition positionPreference) { this->positionPreference = positionPreference; }
	inline void toggleVisible() { visible = ! visible; }
	inline void toggleActive() { active = ! active; }
	inline void toggleBorderEnabled() { borderEnabled = ! borderEnabled; }
	inline void setFont(Font* font) { renderer->font = font; }
	inline std::string getName() { return name; }
	inline bool isVisible() { return visible; }
	inline bool isActive() { return active; }
	inline bool isRepeatClickedEventsEnabled() { return repeatClickedEvents; }
	inline GUIGroup* getGroup() { return group; }
	inline bool belongsToGroup() { return group != NULL; }
	inline GUIBorder* getBorder() { return border; }
	inline bool hasBorder() { return border != NULL; }
	inline bool isBorderEnabled() { return borderEnabled; }
	inline std::vector<GUIComponent*> getComponents() { return components; }
	inline GUIPosition getPositionPreference() { return positionPreference; }
	inline bool isClicked() { return clicked; }
};

/***************************************************************************************************/

/***************************************************************************************************
 * The GUIGroup class
 ***************************************************************************************************/

class GUIGroup : public GUIComponent {
private:
	std::vector<GUIComponent*> m_groupComponents;
public:
	GUIGroup(std::string name);
	virtual ~GUIGroup() {}
	void updateComponent() override;
	void renderComponent() override;
	void add(GUIComponent* component);
	void remove(GUIComponent* component);
	inline void clear() { m_groupComponents.clear(); }
	inline void setGroupComponents(std::vector<GUIComponent*> groupComponents) {
		m_groupComponents = groupComponents;
	}
	inline std::vector<GUIComponent*> getGroupComponents() { return m_groupComponents; }
};

/***************************************************************************************************/

/***************************************************************************************************
 * The GUIBorder class
 ***************************************************************************************************/

class GUIBorder : public Object2D {
private:
	float m_thickness;
	std::vector<Colour> m_colours;
	std::vector<Texture*> m_textures;
public:
	GUIComponent* component;
	GUIComponentRenderer* renderer;
	GUIBorder();
	GUIBorder(GUIComponent* component, float thickness);
	GUIBorder(float thickness, Colour colour);
	GUIBorder(float thickness, Texture* texture);
	GUIBorder(GUIComponent* component, float thickness, Colour colour);
	GUIBorder(GUIComponent* component, float thickness, Texture* texture);
	GUIBorder(GUIComponent* component, float thickness, std::vector<Colour> colours);
	GUIBorder(GUIComponent* component, float thickness, std::vector<Texture*> textures);
	void setup(GUIComponent* component);
	void render();

	inline float getThickness() { return m_thickness; }

	void setColour(Colour colour);
	void setTexture(Texture* texture);
	Colour getColour();
	Texture* getTexture();

	inline bool hasColour() { return m_colours.size() > 0; }
	inline bool hasTexture() { return m_textures.size() > 0; }
};

/***************************************************************************************************/

/***************************************************************************************************
 * The GUILabel class
 ***************************************************************************************************/

class GUILabel : public GUIComponent {
private:
	std::string m_text;
public:
	GUILabel(std::string text);
	GUILabel(std::string text, Font* font);
	void renderComponent() override { renderText(m_text); }
	void setText(std::string text);
	void setFont(Font* font);
	inline std::string getText() { return m_text; }
};

/***************************************************************************************************/

/***************************************************************************************************
 * The GUIToolTip class
 ***************************************************************************************************/

class GUIToolTip : public GUIComponentListener {
public:
	GUILabel* label;
	GUIComponent* component;
	Timer* timer;
	long time;
	bool showing;

	GUIToolTip(std::string text);
	GUIToolTip(GUIComponent* component, std::string text);
	GUIToolTip(std::string text, Colour colour);
	GUIToolTip(GUIComponent* component, std::string text, Colour colour);

	void setComponent(GUIComponent* component);

	void update();
	void render();

	virtual void onMouseEnter(GUIComponent* component) override;
	virtual void onMouseLeave(GUIComponent* component) override;
	virtual void onClicked(GUIComponent* component) override;
};

/***************************************************************************************************/

/***************************************************************************************************
 * The GUIFill class
 ***************************************************************************************************/

class GUIFill : public Object2D {
public:
	GUIComponent* component;
	GUIComponentRenderer* renderer;
	Colour colour;
	Texture* texture;
	float lastWidth;
	float lastHeight;
	GUIFill() {
		component = NULL;
		renderer = NULL;
		texture = NULL;
		colour = Colour(-1, -1, -1, -1);
		lastWidth = 0;
		lastHeight = 0;
	}
	GUIFill(GUIComponent* component) {
		setup(component);
	}
	GUIFill(GUIComponent* component, Colour colour) {
		setup(component);
		this->colour = colour;
	}
	GUIFill(GUIComponent* component, Texture* texture) {
		setup(component);
		this->texture = texture;
	}
	void setup(GUIComponent* component);
	void setTexture(Texture* texture);
	void update();
	void render();
};

/***************************************************************************************************/

/***************************************************************************************************
 * The GUITexture class
 ***************************************************************************************************/

class GUITexture : public GUIComponent {
public:
	GUITexture(Texture* texture) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(texture->getWidth(), texture->getHeight(), texture, Colour::WHITE))) {
		setSize(texture->getWidth(), texture->getHeight());
		renderer->textures.push_back(texture);
		renderer->colours.push_back(Colour::WHITE);
	}
	GUITexture(Texture* texture, Colour colour) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(texture->getWidth(), texture->getHeight(), texture, Colour::WHITE))) {
		setSize(texture->getWidth(), texture->getHeight());
		renderer->textures.push_back(texture);
		renderer->colours.push_back(colour);
	}
	GUITexture(Texture* texture, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, texture, Colour::WHITE))) {
		setSize(width, height);
		renderer->textures.push_back(texture);
		renderer->colours.push_back(Colour::WHITE);
	}
	GUITexture(Texture* texture, Colour colour, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, texture, Colour::WHITE))) {
		setSize(width, height);
		renderer->textures.push_back(texture);
		renderer->colours.push_back(colour);
	}
};

/***************************************************************************************************/

#endif /* CORE_GUI_GUICOMPONENT_H_ */
