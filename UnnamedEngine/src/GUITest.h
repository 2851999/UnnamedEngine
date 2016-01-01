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

#include "core/CoreEngine.h"
#include "core/gui/Font.h"

//#include "core/gui/GUIComponent.h"
#include "core/gui/GUIButton.h"
#include "core/gui/GUICheckBox.h"
#include "core/gui/GUIDropDownMenu.h"
#include "core/gui/GUIDropDownList.h"
#include "core/gui/GUIRadioCheckBox.h"
#include "core/gui/GUITextBox.h"
#include "core/gui/GUILoadingBar.h"
#include "core/gui/GUISlider.h"
#include "core/gui/GUIWindow.h"
#include "core/gui/GUITextDisplayArea.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>

class GUITest : public Game {
private:
	Camera2D* camera;

	GUIButton* button;
	GUICheckBox* checkBox;
	GUIDropDownMenu* menu;
	GUIDropDownList* list;
	GUIGroup* radio;
	GUIRadioCheckBox* radio1;
	GUIRadioCheckBox* radio2;
	GUIRadioCheckBox* radio3;
	GUILabel* label;
	GUITextBox* textBox;
	GUILoadingBar* loadingBar;
	GUISlider* verticalSlider;
	GUISlider* horizontalSlider;
	GUIWindow* window;
	GUITextDisplayArea* displayArea;
public:
	virtual ~GUITest() {}
	virtual void initialise(Settings* settings);
	virtual void created();
	virtual void update();
	virtual void render();
	virtual void destroy();
	void onKeyPressed(int code);
	void onKeyReleased(int code) {}
	void onKeyTyped(int code) {}
	void onChar(int code, char character) {}
	void onMousePressed(int button) {}
	void onMouseReleased(int button) {}
	void onMouseClicked(int button) {}
	void onMouseMoved(double x, double y, double dx, double dy) {}
	void onMouseDragged(double x, double y, double dx, double dy) {}
	void onMouseEnter() {}
	void onMouseLeave() {}
};

void GUITest::initialise(Settings* settings) {
	settings->setVideoSamples(16);
}

void GUITest::created() {
	//Renderer::initialise();
	//camera = Camera2D(Matrix4f().setOrphographic(0, 1280, 720, 0, -1, 1));
	camera = new Camera2D(Matrix4f().initOrthographic(0, getSettings()->getWindowWidth(), getSettings()->getWindowHeight(), 0, -1, 1));
	camera->update();
	Renderer::addCamera(camera);

	std::vector<Colour> colours;
	colours.push_back(Colour::LIGHT_BLUE);
	colours.push_back(Colour::BLUE);
	colours.push_back(Colour::RED);

	button = new GUIButton("Click Me", colours, 100, 20);
	button->name = "Button";
	button->setPosition(20, 100);
	button->toolTip = new GUIToolTip(button, "Please Click Me!", Colour(Colour::GREY, 0.9f));

	checkBox = new GUICheckBox(colours, 20, 20);
	checkBox->name = "CheckBox";
	checkBox->setPosition(140, 100);

	menu = new GUIDropDownMenu(new GUIButton("File", colours, 100, 20));
	menu->addButton(new GUIButton("Save", colours, 100, 20));
	menu->addButton(new GUIButton("Save As", colours, 100, 20));
	menu->setPosition(180, 100);

	list = new GUIDropDownList(new GUIButton("800 x 600", colours, 120, 20));
	list->addButton(new GUIButton("1024 x 720", colours, 120, 20));
	list->addButton(new GUIButton("1920 x 1080", colours, 120, 20));
	list->setPosition(300, 100);

	radio = new GUIGroup("RadioButtons");
	radio->setPosition(20, 200);

	radio1 = new GUIRadioCheckBox("Option 1", colours, 20, 20);
	radio1->setPosition(0, 0);
	radio2 = new GUIRadioCheckBox("Option 2", colours, 20, 20);
	radio2->setPosition(0, 30);
	radio3 = new GUIRadioCheckBox("Option 3", colours, 20, 20);
	radio3->setPosition(0, 60);

	radio->add(radio1);
	radio->add(radio2);
	radio->add(radio3);

	radio->setSize(120, 80);
	radio->border = new GUIBorder(radio, 1.0f, Colour(Colour::LIGHT_BLUE, 0.3f));
	radio->borderEnabled = true;

	textBox = new GUITextBox(Colour::WHITE, 200, 20);
	textBox->renderer->font = Font::loadFont("H:/Andor/test2.png", 16, 18);
	textBox->setPosition(20, 300);
	textBox->setDefaultText("Enter something");
	textBox->border = new GUIBorder(textBox, 1.0f, Colour::LIGHT_BLUE);
	textBox->borderEnabled = true;
	textBox->selection->setColour(Colour(Colour::LIGHT_BLUE, 0.2f));

	loadingBar = new GUILoadingBar(10, Colour::WHITE, 300, 20);
	loadingBar->setPosition(20, 340);
	loadingBar->border = new GUIBorder(loadingBar, 1.0f, Colour::LIGHT_BLUE);
	loadingBar->borderEnabled = true;
	loadingBar->setCurrentStage(2);
	loadingBar->setFillColour(Colour::LIGHT_BLUE);

	GUIButton* verticalSliderButton = new GUIButton("", colours, 26, 10);
	verticalSlider = new GUISlider(verticalSliderButton, GUISlider::DIRECTION_VERTICAL, 4, 100);
	verticalSlider->setPosition(20, 400);

	GUIButton* horizontalSliderButton = new GUIButton("", colours, 10, 26);
	horizontalSlider = new GUISlider(horizontalSliderButton, GUISlider::DIRECTION_HORIZONTAL, 100, 4);
	horizontalSlider->setPosition(100, 400);

	std::vector<Colour> closeColours;
	closeColours.push_back(Colour::RED);
	closeColours.push_back(Colour::BLUE);
	closeColours.push_back(Colour::LIGHT_BLUE);

	GUIButton* closeButton = new GUIButton("X", closeColours, 30, 20);
	window = new GUIWindow("Window", Colour::WHITE, 200, 120);
	window->setBarColour(Colour::LIGHT_BLUE);
	window->setPosition(400, 200);
	window->setCloseButton(closeButton);

	displayArea = new GUITextDisplayArea("Hello how are you today. This will hopefully work but I have no idea.", 200);
	displayArea->setPosition(400, 400);
}

void GUITest::update() {
	button->update();
	checkBox->update();
	menu->update();
	list->update();
	radio->update();
	textBox->update();
	loadingBar->update();
	verticalSlider->update();
	horizontalSlider->update();
	window->update();
	displayArea->update();
}

void GUITest::render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//std::cout << textBox->selection->renderer->colours[0].toString() << std::endl;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	button->render();
	checkBox->render();
	menu->render();
	list->render();
	radio->render();
	textBox->render();
	loadingBar->render();
	verticalSlider->render();
	horizontalSlider->render();
	window->render();
	displayArea->render();

	renderInformation();
}

void GUITest::destroy() {

}

void GUITest::onKeyPressed(int key) {
	if (key == GLFW_KEY_ESCAPE)
		requestClose();
}
