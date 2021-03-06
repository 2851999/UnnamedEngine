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

#ifndef CORE_GUI_GUITEXTBOX_H_
#define CORE_GUI_GUITEXTBOX_H_

#include "../input/Input.h"
#include "../input/KeyboardShortcuts.h"
#include "GUIComponent.h"

/***************************************************************************************************
 * The GUITextBoxCursor class
 ***************************************************************************************************/

class GUITextBox;

class GUITextBoxCursor : public Object2D {
public:
	GUITextBox* textBox;
	GUIComponentRenderer* renderer;
	Timer* timer;
	long timeBetweenBlink;
	bool cursorShown;
	Colour colour;
	Texture* texture;

	GUITextBoxCursor();
	GUITextBoxCursor(GUITextBox* textBox, float thickness);

	void setup(GUITextBox* textBox);

	void setColour(Colour colour);
	void setTexture(Texture* texture);
	Colour getColour();
	Texture* getTexture();
	bool hasColour();
	bool hasTexture();

	void render();

	void showCursor();

	inline void setTimeBetweenBlink(long timeBetweenBlink) { this->timeBetweenBlink = timeBetweenBlink; }
	inline long getTimeBetweenBlink() { return timeBetweenBlink; }
	inline bool isCursorShowing() { return cursorShown; }
};

/***************************************************************************************************/

/***************************************************************************************************
 * The GUITextBoxSelection class
 ***************************************************************************************************/

class GUITextBoxSelection : public Object2D {
public:
	GUITextBox* textBox;
	GUIComponentRenderer* renderer;
	Colour colour;
	Texture* texture;

	GUITextBoxSelection();
	GUITextBoxSelection(GUITextBox* textBox);

	void setup(GUITextBox* textBox);

	void setColour(Colour colour);
	void setTexture(Texture* texture);
	Colour getColour();
	Texture* getTexture();
	bool hasColour();
	bool hasTexture();

	void render();
};

/***************************************************************************************************/

/***************************************************************************************************
 * The GUITextBox class
 ***************************************************************************************************/

class GUITextBox : public GUIComponent, InputListener, KeyboardShortcutListener {
public:
	std::string text;
	std::string renderText;
	bool selected;
	bool masked;
	std::string mask;
	std::string defaultText;
	Font* defaultTextFont;
	unsigned int cursorIndex;
	GUITextBoxCursor* cursor;

	unsigned int viewIndexStart;
	unsigned int viewIndexEnd;

	bool isSelection;

	unsigned int selectionIndexStart;
	unsigned int selectionIndexEnd;

	GUITextBoxSelection* selection;

	KeyboardShortcuts* shortcuts;

	GUITextBox(float width, float height);
	GUITextBox(Colour colour, float width, float height);
	GUITextBox(Texture* texture, float width, float height);
	GUITextBox(Texture* texture, Colour colour, float width, float height);

	void setColour(Colour colour);
	void setTexture(Texture* texture);
	Colour getColour();
	Texture* getTexture();
	bool hasColour();
	bool hasTexture();

	void setup();

	virtual void updateComponent() override;
	virtual void renderComponent() override;

	void updateRenderText();
	std::string maskStr(std::string s, std::string mask);

	void clipRenderText();

	void moveCursor(double x);

	int getIndex(double x);

	void resetSelection();

	std::string getSelection();

	std::string getRenderTextSelection();

	void deleteSelection();

	virtual void componentOnClicked() override;

	virtual void onKeyPressed(int code) override;

	virtual void onChar(int code, char character) override;

	virtual void onMousePressed(int button) override;

	virtual void onMouseDragged(double x, double y, double dx, double dy) override;

	virtual void onShortcut(KeyboardShortcut* e) override;

	bool isDefined(char character);

	bool shouldUseDefaultText();

	void setText(std::string text);

	inline void setRenderText(std::string renderText) { this->renderText = renderText; }
	inline void setSelected(bool selected) { this->selected = selected; }
	inline void setMasked(bool masked) { this->masked = masked; }
	inline void setMask(std::string mask) { this->mask = mask; }
	inline void setDefaultText(std::string defaulttext) { this->defaultText = defaultText; }
	inline void setDefaultTextFont(Font* defaultTextFont) { this->defaultTextFont = defaultTextFont; }
	inline void setCursorIndex(int cursorIndex) { this->cursorIndex = cursorIndex; }
	inline std::string getText() { return text; }
	inline std::string getRenderText() { return renderText; }
	inline bool isSelected() { return selected; }
	inline bool isMasked() { return masked; }
	inline std::string getMask() { return mask; }
	inline std::string getDefaultText() { return defaultText; }
	inline Font* getDefaultTextFont() { return defaultTextFont; }
	inline int getCursorIndex() { return cursorIndex; }
};

/***************************************************************************************************/

#endif /* CORE_GUI_GUITEXTBOX_H_ */
