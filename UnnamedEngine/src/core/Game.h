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

#ifndef CORE_GAME_H_
#define CORE_GAME_H_

#include "../utils/FPSCalculator.h"
#include "input/Input.h"
#include "gui/Font.h"
#include "Settings.h"
#include "Camera.h"
#include "Window.h"

/***************************************************************************************************
 * The Game class consists of the settings and window for a game and will also handle the main
 * game loop
 ***************************************************************************************************/

class Game : public InputListener {
private:
	/* The default font and camera used to render debug information */
	Font* m_font;
	Camera2D* m_camera;

	/* The window instance everything is rendered to */
	Window*  m_window;

	/* The current game settings */
	Settings* m_settings;

	/* The FPS calculator used to calculate the FPS and delta time */
	FPSCalculator* m_fpsCalculator;

	/* A boolean used to request the game to stop */
	bool m_closeRequested;
public:
	/* The current instance of the game */
	static Game* current;

	/* The default constructor */
	Game() {
		m_font = NULL;
		m_window = NULL;
		m_closeRequested = false;
		m_settings = new Settings();
		m_fpsCalculator = new FPSCalculator();
		m_camera = NULL;
	}
	virtual ~Game() {}

	/* This method is called to start the main game loop */
	void create();

	/* This method renders debug information */
	void renderInformation();

	/* Methods that should be implemented by the game */
	virtual void initialise(Settings* settings) {}
	virtual void created() {}
	virtual void update() {}
	virtual void render() {}
	virtual void destroy() {}

	/* Input methods inherited from the InputListener */
	void onKeyPressed(int code) override {}
	void onKeyReleased(int code) override {}
	void onKeyTyped(int code) override {}
	void onChar(int code, char character) override {}

	void onMousePressed(int button) override {}
	void onMouseReleased(int button) override {}
	void onMouseClicked(int button) override {}
	void onMouseMoved(double x, double y, double dx, double dy) override {}
	void onMouseDragged(double x, double y, double dx, double dy) override {}
	void onMouseEnter() override {}
	void onMouseLeave() override {}

	void onScroll(double dx, double dy) override {}

	/* This method simply tells the game to stop */
	inline void requestClose() { m_closeRequested = true; }

	/* The setters and getters */
	inline FPSCalculator* getFPSCalculator() { return m_fpsCalculator; }
	inline long getDelta() { return m_fpsCalculator->getDelta(); }
	inline float getFPS() { return m_fpsCalculator->getFPS(); }

	Window* getWindow() { return m_window; }
	Settings* getSettings() { return m_settings; }
};

#endif
