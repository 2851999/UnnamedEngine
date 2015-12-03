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

#include <cctype>
#include "../../utils/ClipboardUtils.h"
#include "GUITextBox.h"

/***************************************************************************************************
 * The GUITextBoxCursor class
 ***************************************************************************************************/

GUITextBoxCursor::GUITextBoxCursor() {
	timer = NULL;
	timeBetweenBlink = 0;
	cursorShown = false;
	texture = NULL;
	textBox = NULL;
	renderer = NULL;
	colour = Colour(-1.0f, -1.0f, -1.0f, -1.0f);
}

GUITextBoxCursor::GUITextBoxCursor(GUITextBox* textBox, float thickness) {
	colour = Colour(-1.0f, -1.0f, -1.0f, -1.0f);
	setWidth(thickness);
	setup(textBox);
}

void GUITextBoxCursor::setup(GUITextBox* textBox) {
	this->textBox = textBox;
	setHeight(textBox->renderer->font->getHeight("A"));
	renderer = new GUIComponentRenderer(MeshBuilder::createQuad(getWidth(), getHeight(), Colour::WHITE));
	renderer->colours.push_back(Colour::BLACK);
	timer = new Timer();
	timer->start();
	timeBetweenBlink = 600;
	cursorShown = false;
	if (colour.getR() != -1.0f)
		setColour(colour);
	if (texture != NULL)
		setTexture(texture);
}

void GUITextBoxCursor::setColour(Colour colour) {
	renderer->colours.clear();
	renderer->colours.push_back(colour);
}

void GUITextBoxCursor::setTexture(Texture* texture) {
	renderer->textures.clear();
	renderer->textures.push_back(texture);
}

Colour GUITextBoxCursor::getColour() {
	if (renderer->colours.size() > 0)
		return renderer->colours[0];
	else
		return Colour::NONE;
}

Texture* GUITextBoxCursor::getTexture() {
	if (renderer->textures.size() > 0)
		return renderer->textures[0];
	else
		return NULL;
}

bool GUITextBoxCursor::hasColour() {
	return renderer->colours.size() > 0;
}

bool GUITextBoxCursor::hasTexture() {
	return renderer->textures.size() > 0;
}

void GUITextBoxCursor::render() {
	if (timer->hasTimePassed(timeBetweenBlink)) {
		cursorShown = ! cursorShown;
		timer->restart();
	}
	if (cursorShown) {
		Vector2f p = textBox->getPosition();
		float x = 1 + p.getX() + (textBox->renderer->font->getWidth(textBox->renderText.substr(0, textBox->cursorIndex - textBox->viewIndexStart)));
		float y = (p.getY() + (textBox->getHeight() / 2)) - (getHeight() / 2);
		setPosition(x, y);
		renderer->render(this, textBox->active);
	}
}

void GUITextBoxCursor::showCursor() {
	timer->restart();
	cursorShown = true;
}

/***************************************************************************************************/

/***************************************************************************************************
 * The GUITextBoxSelection class
 ***************************************************************************************************/

GUITextBoxSelection::GUITextBoxSelection() {
	textBox = NULL;
	texture = NULL;
	renderer = NULL;
	colour = Colour(-1.0f, -1.0f, -1.0f, -1.0f);
}

GUITextBoxSelection::GUITextBoxSelection(GUITextBox* textBox) {
	colour = Colour(-1.0f, -1.0f, -1.0f, -1.0f);
	setup(textBox);
}

void GUITextBoxSelection::setup(GUITextBox* textBox) {
	this->textBox = textBox;
	setSize(0, 0);
	renderer = new GUIComponentRenderer(MeshBuilder::createQuad(getWidth(), getHeight(), Colour::WHITE));
	renderer->colours.push_back(Colour::BLACK);
	if (colour.getR() != -1.0f)
		setColour(colour);
	if (texture != NULL)
		setTexture(texture);
}

void GUITextBoxSelection::setColour(Colour colour) {
	renderer->colours.clear();
	renderer->colours.push_back(colour);
}

void GUITextBoxSelection::setTexture(Texture* texture) {
	renderer->textures.clear();
	renderer->textures.push_back(texture);
}

Colour GUITextBoxSelection::getColour() {
	if (renderer->colours.size() > 0)
		return renderer->colours[0];
	else
		return Colour::NONE;
}

Texture* GUITextBoxSelection::getTexture() {
	if (renderer->textures.size() > 0)
		return renderer->textures[0];
	else
		return NULL;
}

bool GUITextBoxSelection::hasColour() {
	return renderer->colours.size() > 0;
}

bool GUITextBoxSelection::hasTexture() {
	return renderer->textures.size() > 0;
}

void GUITextBoxSelection::render() {
	if (textBox->isSelection) {
		Vector2f p = textBox->getPosition();
		float selectionX = 0;
		try {
			if (textBox->selectionIndexStart < textBox->selectionIndexEnd)
				selectionX = p.getX() + textBox->renderer->font->getWidth(textBox->renderText.substr(0, textBox->selectionIndexStart - textBox->viewIndexStart));
			else
				selectionX = p.getX() + textBox->renderer->font->getWidth(textBox->renderText.substr(0, textBox->selectionIndexEnd - textBox->viewIndexStart));
		} catch (int e) {

		}
		float selectionY = p.getY();
		float selectionWidth = textBox->renderer->font->getWidth(textBox->getRenderTextSelection());
		float selectionHeight = textBox->getHeight();
		renderer->entity->getMesh()->getData()->clearPositions();
		MeshBuilder::addQuadV(renderer->entity->getMesh()->getData(), selectionWidth, selectionHeight);
		renderer->entity->getMesh()->updateVertices();
		position = Vector2f(selectionX, selectionY);
		renderer->render(this, textBox->active);
	}
}

/***************************************************************************************************/

/***************************************************************************************************
 * The GUITextBox class
 ***************************************************************************************************/

GUITextBox::GUITextBox(float width, float height) :
	GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, Colour::WHITE), width, height)) {
	setup();
}

GUITextBox::GUITextBox(Colour colour, float width, float height) :
	GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, Colour::WHITE), width, height)) {
	renderer->colours.push_back(colour);
	setup();
}

GUITextBox::GUITextBox(Texture* texture, float width, float height) :
	GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, texture, Colour::WHITE), width, height)) {
	renderer->textures.push_back(texture);
	setup();
}

GUITextBox::GUITextBox(Texture* texture, Colour colour, float width, float height) :
	GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, texture, Colour::WHITE), width, height)) {
	renderer->colours.push_back(colour);
	renderer->textures.push_back(texture);
	setup();
}

void GUITextBox::setColour(Colour colour) {
	renderer->colours.clear();
	renderer->colours.push_back(colour);
}

void GUITextBox::setTexture(Texture* texture) {
	renderer->textures.clear();
	renderer->textures.push_back(texture);
}

Colour GUITextBox::getColour() {
	if (renderer->colours.size() > 0)
		return renderer->colours[0];
	else
		return Colour::NONE;
}

Texture* GUITextBox::getTexture() {
	if (renderer->textures.size() > 0)
		return renderer->textures[0];
	else
		return NULL;
}

bool GUITextBox::hasColour() {
	return renderer->colours.size() > 0;
}

bool GUITextBox::hasTexture() {
	return renderer->textures.size() > 0;
}

void GUITextBox::setup() {
	InputManager::addListener(this);

	text = "";
	renderText = "";
	selected = false;
	masked = false;
	mask = "*";
	defaultText = "";
	cursorIndex = 0;
	cursor = new GUITextBoxCursor(this, 1.0f);
	viewIndexStart = 0;
	viewIndexEnd = 0;
	isSelection = false;
	selectionIndexStart = 0;
	selectionIndexEnd = 0;
	selection = new GUITextBoxSelection(this);
	shortcuts = new KeyboardShortcuts();
	shortcuts->addListener(this);

	std::vector<int> shiftLeftKeys1;
	shiftLeftKeys1.push_back(GLFW_KEY_LEFT_SHIFT);
	shiftLeftKeys1.push_back(GLFW_KEY_LEFT);
	std::vector<int> shiftLeftKeys2;
	shiftLeftKeys2.push_back(GLFW_KEY_RIGHT_SHIFT);
	shiftLeftKeys2.push_back(GLFW_KEY_LEFT);

	std::vector<int> shiftRightKeys1;
	shiftRightKeys1.push_back(GLFW_KEY_LEFT_SHIFT);
	shiftRightKeys1.push_back(GLFW_KEY_RIGHT);
	std::vector<int> shiftRightKeys2;
	shiftRightKeys2.push_back(GLFW_KEY_RIGHT_SHIFT);
	shiftRightKeys2.push_back(GLFW_KEY_RIGHT);

	std::vector<int> cutKeys1;
	cutKeys1.push_back(GLFW_KEY_LEFT_CONTROL);
	cutKeys1.push_back(GLFW_KEY_X);
	std::vector<int> cutKeys2;
	cutKeys2.push_back(GLFW_KEY_RIGHT_CONTROL);
	cutKeys2.push_back(GLFW_KEY_X);

	std::vector<int> copyKeys1;
	copyKeys1.push_back(GLFW_KEY_LEFT_CONTROL);
	copyKeys1.push_back(GLFW_KEY_C);
	std::vector<int> copyKeys2;
	copyKeys2.push_back(GLFW_KEY_RIGHT_CONTROL);
	copyKeys2.push_back(GLFW_KEY_C);

	std::vector<int> pasteKeys1;
	pasteKeys1.push_back(GLFW_KEY_LEFT_CONTROL);
	pasteKeys1.push_back(GLFW_KEY_V);
	std::vector<int> pasteKeys2;
	pasteKeys2.push_back(GLFW_KEY_RIGHT_CONTROL);
	pasteKeys2.push_back(GLFW_KEY_V);

	shortcuts->add(new KeyboardShortcut("Shift-Left", shiftLeftKeys1));
	shortcuts->add(new KeyboardShortcut("Shift-Left", shiftLeftKeys2));

	shortcuts->add(new KeyboardShortcut("Shift-Right", shiftRightKeys1));
	shortcuts->add(new KeyboardShortcut("Shift-Right", shiftRightKeys2));

	shortcuts->add(new KeyboardShortcut("Cut", cutKeys1));
	shortcuts->add(new KeyboardShortcut("Cut", cutKeys2));

	shortcuts->add(new KeyboardShortcut("Copy", copyKeys1));
	shortcuts->add(new KeyboardShortcut("Copy", copyKeys2));

	shortcuts->add(new KeyboardShortcut("Paste", pasteKeys1));
	shortcuts->add(new KeyboardShortcut("Paste", pasteKeys2));
}

void GUITextBox::updateComponent() {}

void GUITextBox::renderComponent() {
	Font* f = renderer->font;
	if (shouldUseDefaultText()) {
		renderText = defaultText;
		if (defaultTextFont != NULL)
			f = defaultTextFont;
	} else {
		updateRenderText();
		clipRenderText();
	}

	Vector2f p = getPosition();

	float textX = p.getX() + 1;
	float textY = (p.getY() + (getHeight() / 2) - (f->getHeight(renderText) / 2));

	f->render(renderText, textX, textY);

	if (selected)
		cursor->render();
	selection->render();
}

void GUITextBox::updateRenderText() {
	//Try and prevent any problems with the view index being out of bounds by accident
	if (viewIndexStart < 0)
		viewIndexStart = 0;
	if (viewIndexEnd > text.length())
		viewIndexEnd = text.length();

	renderText = text.substr(viewIndexStart, viewIndexEnd);

	if (masked)
		renderText = maskStr(renderText, mask);
}

std::string GUITextBox::maskStr(std::string s, std::string mask) {
	std::string maskedString = "";
	for (unsigned int a = 0; a < s.length(); a++)
		maskedString += mask;
	return maskedString;
}

void GUITextBox::clipRenderText() {
	float width = getWidth();
	while (renderer->font->getWidth(renderText) >= width - 2 && cursorIndex != viewIndexStart) {
		viewIndexStart++;
		updateRenderText();
	}
	while (renderer->font->getWidth(renderText) >= width && cursorIndex <= viewIndexEnd) {
		viewIndexEnd--;
		updateRenderText();
	}
}

void GUITextBox::moveCursor(double x) {
	cursorIndex = getIndex(x);
	cursor->showCursor();
}

int GUITextBox::getIndex(double x) {
	updateRenderText(); //Is this really necessary??
	const char* textValue = renderText.c_str();
	std::string currentString = "";
	int newPlace = 0;

	for (unsigned int a = 0; a < renderText.length(); a++) {
		currentString += textValue[a];

		double lookX = 0;
		double widthOfString = renderer->font->getWidth(currentString);
		double widthOfLastCharacter = renderer->font->getWidth(currentString.substr(currentString.length() - 1));

		//Add onto lookX the position this text box starts rendering the text
		lookX += position.getX() + 1;
		//Add onto lookX the width of the string - (the width of the last character / 2)
		lookX += widthOfString - (widthOfLastCharacter / 2);

		if (lookX < x)
			newPlace++;
		else
			break;
	}
	newPlace += viewIndexStart;
	return newPlace;
}

void GUITextBox::resetSelection() {
	isSelection = false;
	selectionIndexStart = 0;
	selectionIndexEnd = 0;
}

std::string GUITextBox::getSelection() {
	if (isSelection) {
		if (selectionIndexStart < selectionIndexEnd)
			return text.substr(selectionIndexStart, selectionIndexEnd);
		else
			return text.substr(selectionIndexEnd, selectionIndexStart);
	} else
		return "";
}

std::string GUITextBox::getRenderTextSelection() {
	if (isSelection) {
		updateRenderText();
		clipRenderText();

		unsigned int sis = selectionIndexStart;
		if (sis < viewIndexStart)
			sis = viewIndexStart;
		else if (sis > viewIndexEnd)
			sis = viewIndexEnd;

		unsigned int sie = selectionIndexEnd;
		if (sie < viewIndexStart)
			sie = viewIndexStart;
		else if (sie > viewIndexEnd)
			sie = viewIndexEnd;

		if (selectionIndexStart <= selectionIndexEnd)
			return renderText.substr(sis - viewIndexStart, sie - viewIndexStart);
		else
			return renderText.substr(sie - viewIndexStart, sis - viewIndexStart);
	} else
		return "";
}

void GUITextBox::deleteSelection() {
	std::string front = "";
	std::string back = "";

	if (selectionIndexStart < selectionIndexEnd) {
		front = text.substr(0, selectionIndexStart);
		back = text.substr(selectionIndexEnd);
	} else {
		front = text.substr(0, selectionIndexEnd);
		back = text.substr(selectionIndexStart);
	}

	int amountRemoved = text.length() - (front + back).length();

	int a = 0;

	while (a < amountRemoved) {
		if (viewIndexStart > 0)
			viewIndexStart--;
		a++;
	}
	text = front + back;

	if (cursorIndex > text.length())
		cursorIndex = text.length();

	resetSelection();
}

void GUITextBox::componentOnClicked() {
	selected = true;
	cursor->showCursor();
}

void GUITextBox::onKeyPressed(int code) {
	if (visible && active && selected) {
		if (code == GLFW_KEY_BACKSPACE) {
			if (isSelection)
				deleteSelection();
			else {
				if (text.length() > 0 && cursorIndex > 0) {
					std::string front = text.substr(0, cursorIndex);
					std::string back = text.substr(cursorIndex);

					text = front.substr(0, front.length() - 1) + back;

					if (cursorIndex == viewIndexStart) {
						cursorIndex --;
						if (viewIndexStart > 0)
							viewIndexStart--;
						viewIndexEnd--;
					} else {
						cursorIndex--;
						viewIndexEnd--;

						if (viewIndexStart > 0)
							viewIndexStart--;
						else
							viewIndexEnd++;
					}
				}
			}
		} else if (code == GLFW_KEY_DELETE) {
			if (isSelection)
				deleteSelection();
			else {
				std::string front = text.substr(0, cursorIndex);
				std::string back = text.substr(cursorIndex);

				text = front + back.substr(1);

				if (! (viewIndexEnd <= text.length())) {
					//Decrement the view's end index
					viewIndexEnd--;
					//Decrement the view's start index (Keeps text at the beginning and end)
					viewIndexStart--;
				}
			}
		} else if (code == GLFW_KEY_LEFT && ! Keyboard::isPressed(GLFW_KEY_LEFT_SHIFT) && ! Keyboard::isPressed(GLFW_KEY_RIGHT_SHIFT)) {
			resetSelection();
			//Make sure the cursor's current index is more than 0
			if (cursorIndex > 0) {
				//Check the cursor index and viewing index
				if (cursorIndex == viewIndexStart) {
					//Check to see whether there is any unseen text
					if (viewIndexStart > 0) {
						//Decrement the cursor index
						cursorIndex--;
						//Decrement the start of the viewing index
						viewIndexStart--;
					}
				} else {
					//Decrement the cursor index
					cursorIndex--;
				}
			}
			//Show the cursor
			cursor->showCursor();
		} else if (code == GLFW_KEY_RIGHT && ! Keyboard::isPressed(GLFW_KEY_LEFT_SHIFT) && ! Keyboard::isPressed(GLFW_KEY_RIGHT_SHIFT)) {
			resetSelection();
			//Make sure the cursor's current index is less than the length of the text
			if (cursorIndex < text.length()) {
				//Check the cursor index and viewing index
				if (cursorIndex == viewIndexEnd) {
					//Check to see whether there is any unseen text
					if (viewIndexEnd > 0) {
						//Increment the cursor index
						cursorIndex++;
						//Increment the end of the viewing index
						viewIndexEnd++;
					}
				} else {
					//Increment the cursor index
					cursorIndex++;
				}
			}
		}
		//Show the cursor
		cursor->showCursor();
	}
}

void GUITextBox::onChar(int code, char character) {
	if (visible && active && selected) {
		if (code == GLFW_KEY_BACKSPACE) {
		} else if (code == GLFW_KEY_DELETE) {
		} else if (code == GLFW_KEY_LEFT && ! Keyboard::isPressed(GLFW_KEY_LEFT_SHIFT) && ! Keyboard::isPressed(GLFW_KEY_RIGHT_SHIFT)) {
		} else if (code == GLFW_KEY_RIGHT && ! Keyboard::isPressed(GLFW_KEY_LEFT_SHIFT) && ! Keyboard::isPressed(GLFW_KEY_RIGHT_SHIFT)) {
		} else {
			if (isDefined(character)) {
				if (isSelection)
					deleteSelection();
				std::string front = text.substr(0, cursorIndex);
				std::string back = text.substr(cursorIndex);

				text = front + character + back;

				//Check the viewing index and cursor index
				if (viewIndexStart == cursorIndex && viewIndexStart > 0) {
					//Increase the cursor index
					cursorIndex++;
				} else {
					//Increase the cursor index
					cursorIndex++;
					viewIndexEnd++;
				}
			}
		}
		//Show the cursor
		cursor->showCursor();
	}
}

void GUITextBox::onMousePressed(int button) {
	if (! mouseHoveringInside)
		selected = false;
	else if (selected && button == GLFW_MOUSE_BUTTON_LEFT) {
		moveCursor(Mouse::lastX);
		resetSelection();
	}
}

void GUITextBox::onMouseDragged(double x, double y, double dx, double dy) {
	//Make sure this is selected
	if (visible && active && selected) {
		//Check to see whether there is a selection
		if (! isSelection) {
			//Set the selection values
			selectionIndexStart = getIndex(x);
			selectionIndexEnd = selectionIndexStart;
			isSelection = true;
		} else {
			//Set the new selection index end
			selectionIndexEnd = getIndex(x);
			//Move the cursor
			moveCursor(x);

			//Check the index values
			if (viewIndexStart == cursorIndex) {
				//Keep some text visible if there is more
				if (cursorIndex > 0)
					cursorIndex--;
				if (viewIndexStart > 0)
					viewIndexStart--;
				if (selectionIndexEnd > 0)
					selectionIndexEnd--;
			}
			if (viewIndexEnd == cursorIndex) {
				//Keep some text visible if there is more
				if (cursorIndex < text.length())
					cursorIndex++;
				if (viewIndexEnd < text.length())
					viewIndexEnd++;
				if (selectionIndexEnd < text.length())
					selectionIndexEnd++;
			}
		}
	}
}

void GUITextBox::onShortcut(KeyboardShortcut* e) {
	if (e->name == "Shift-Left") {
		//Make sure the cursor's current index is more than 0
		if (cursorIndex > 0) {
			//Check the cursor index and viewing index
			if (cursorIndex == viewIndexStart) {
				//Check to see whether there is any unseen text
				if (viewIndexStart > 0) {
					//Decrement the cursor index
					cursorIndex--;
					//Decrement the start of the viewing index
					viewIndexStart--;
				}
			} else {
				//Decrement the cursor index
				cursorIndex--;
			}
		}
		if (! isSelection) {
			isSelection = true;
			selectionIndexStart = cursorIndex + 1;
			selectionIndexEnd = selectionIndexStart;
		}
		if (selectionIndexEnd > 0)
			selectionIndexEnd--;
	} else if (e->name == "Shift-Right") {
		//Make sure the cursor's current index is less than the length of the text
		if (cursorIndex < text.length()) {
			//Check the cursor index and viewing index
			if (cursorIndex == viewIndexEnd) {
				//Check to see whether there is any unseen text
				if (viewIndexEnd > 0) {
					//Increment the cursor index
					cursorIndex++;
					//Increment the end of the viewing index
					viewIndexEnd++;
				}
			} else {
				//Increment the cursor index
				cursorIndex++;
			}
		}
		if (! isSelection) {
			isSelection = true;
			selectionIndexStart = cursorIndex - 1;
			selectionIndexEnd = selectionIndexStart;
		}
		if (selectionIndexEnd < text.length())
			selectionIndexEnd++;
	} else if (e->name == "Cut") {
		if (isSelection) {
			ClipboardUtils::setText(getSelection());
			deleteSelection();
		}
	} else if (e->name == "Paste") {
		if (isSelection)
			deleteSelection();

		std::string front = text.substr(0, cursorIndex);
		std::string back = text.substr(cursorIndex);

		text = front + ClipboardUtils::getText() + back;

		cursorIndex = text.length() - back.length();
		viewIndexEnd = text.length();
	} else if (e->name == "Copy") {
		if (isSelection)
			ClipboardUtils::setText(getSelection());
	}
}

bool GUITextBox::isDefined(char character) {
	return ((character != '\u0000') && (! iscntrl(character)) && isgraph(character) && isprint(character));
}

bool GUITextBox::shouldUseDefaultText() {
	return ! selected && text.length() == 0 && defaultText.length() > 0;
}

void GUITextBox::setText(std::string text) {
	this->text = text;
	viewIndexEnd = text.length();
}

/***************************************************************************************************/
