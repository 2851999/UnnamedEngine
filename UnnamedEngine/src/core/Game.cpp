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

#include "Game.h"
#include "gui/GUIComponent.h"
#include "render/Renderer.h"
#include "ResourceLoader.h"

Game* Game::current;

/* The implementation of the create method */
void Game::create() {
	//Assigns the current game instance and sets up basic variables
	Game::current = this;
	m_settings = new Settings();
	initialise(m_settings);
	m_window = new Window(m_settings);

	//Continue only if the window can be created successfully
	if (m_window->create()) {
		//Assign the window callbacks
		m_window->setKeyCallback(input_callback_key);
		m_window->setCharCallback(input_callback_char);
		m_window->setCursorPosCallback(input_callback_cursorPosition);
		m_window->setCursorEnterCallback(input_callback_cursorEnter);
		m_window->setMouseButtonCallback(input_callback_mouseButton);
		m_window->setScrollCallback(input_callback_scroll);

		//Add an event listener to the game
		addListener();

		//Initialise the rendering system
		Renderer::initialise();

		//Load default resources
		m_font = ResourceLoader::loadFont("resources/textures/font-segoeui.png", 16, 16);
		GUIComponentRenderer::defaultFont = ResourceLoader::loadFont("resources/textures/font-segoeui.png", 16, 16);

		//Setup the debug information camera
		m_camera = new Camera2D(Matrix4f().initOrthographic(0, m_settings->getWindowWidth(), m_settings->getWindowHeight(), 0, -1, 1));
		m_camera->update();

		//Notify the game that the engine has been initalised
		created();

		//The main game loop
		while (! m_window->shouldClose() && ! m_closeRequested) {
			//Update the FPS calculator (Calculates the current FPS and delta time)
			m_fpsCalculator->update();
			//Update and render the game
			update();

			if (m_settings->getVideoDeferredRendering()) {
				Renderer::setShader(Renderer::getShader("DeferredShader"));
				DeferredRenderer::start();
				render();
				DeferredRenderer::stop();
				Renderer::resetShader();

				//Should move this
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glEnable(GL_TEXTURE_2D);
				glDisable(GL_DEPTH_TEST);
				DeferredRenderer::renderToScreen();
			} else
				render();

			//Render the information if needed
			if (m_settings->getDebuggingShowInformation()) {
				//Ensure it can render properly
				glDisable(GL_CULL_FACE);
				glDisable(GL_DEPTH_TEST);

				//Render the information
				renderInformation();
			}
			//Update the window
			m_window->update();
		}
		//Destroy the game and window
		destroy();
		m_window->destroy();
	}
}

/* This method simply renders some information */
void Game::renderInformation() {
	Renderer::addCamera(m_camera);
	m_font->render("DEBUGGING", 0, 0);
	m_font->render("Engine Version:      " + to_string(Settings::ENGINE_VERSION), 0, 24);
	m_font->render("Engine Date:         " + to_string(Settings::ENGINE_DATE), 0, 38);
	m_font->render("Engine Build:        " + to_string(Settings::ENGINE_BUILD), 0, 52);
	m_font->render("Current FPS:         " + to_string(getFPS()), 0, 66);
	m_font->render("Current Delta:       " + to_string(getDelta()), 0, 80);
	m_font->render("------------- VIDEO -------------", 0, 94);
	m_font->render("Resolution:          " + to_string(m_settings->getWindowWidth()) + "x" + to_string(m_settings->getWindowHeight()), 0, 108);
	m_font->render("VSync:               " + to_string(m_settings->getVideoVSync()), 0, 122);
	m_font->render("MSAA Samples:        " + to_string(m_settings->getVideoSamples()), 0, 136);
	m_font->render("Max Anisotropic Samples: " + to_string(m_settings->getVideoMaxAnisotropicSamples()), 0, 150);
	m_font->render("Deferred Rendering:  " + to_string(m_settings->getVideoDeferredRendering()), 0, 164);
	Renderer::removeCamera();
}
