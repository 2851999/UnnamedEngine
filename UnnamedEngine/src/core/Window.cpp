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

#include "Window.h"

/***************************************************************************************************
 * The Window class
 ***************************************************************************************************/

Window::Window(Settings* settings): m_settings(settings) {
	m_instance = NULL;
}

Window::~Window() {
	destroy();
}

bool Window::create() {
	//Initialise GLFW
	if (! glfwInit())
		return false;

	//Setup the window properties
	glfwDefaultWindowHints();
	setResizable(m_settings->getWindowResizable());
	setDecorated(m_settings->getWindowDecorated());
	setSamples(m_settings->getVideoSamples());
	setVSync(m_settings->getVideoVSync());
	setRefreshRate(m_settings->getVideoRefreshRate());
	setFloating(m_settings->getWindowFloating());

	Vector2i resolution = m_settings->getVideoResolution();
	GLFWmonitor* monitor = NULL;

	if (m_settings->getWindowFullscreen()) {
		//Get the primary monitor for running fullscreen
		monitor = glfwGetPrimaryMonitor();

		//Check whether it should be windowed fullscreen mode
		if (m_settings->getWindowBorderless()) {
			//Get the default video mode and setup the window
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		}

		//Create the fullscreen window
		m_instance = glfwCreateWindow(resolution.getX(), resolution.getY(), m_settings->getWindowTitle().c_str(), glfwGetPrimaryMonitor(), NULL);
	} else
		//Create the window
		m_instance = glfwCreateWindow(resolution.getX(), resolution.getY(), m_settings->getWindowTitle().c_str(), monitor, NULL);

	//Exit if the window instance wasn't created properly
	if (! m_instance) {
		glfwTerminate();
		return false;
	}

	//Make this window the current context
	this->makeCurrent();

	//Get the actual rendering space's size
	int width, height;
	glfwGetFramebufferSize(m_instance, &width, &height);
	m_settings->setWindowSize(width, height);

	//Setup OpenGL to use the correct size
	glScissor(0, 0, width, height);
	glViewport(0, 0, width, height);

	//Centre the window if it isn't fullscreen
	if (! m_settings->getWindowFullscreen())
		centre();

	return true;
}

void Window::update() {
	glfwSwapBuffers(m_instance);
	glfwPollEvents();
}

void Window::destroy() {
	glfwDestroyWindow(m_instance);
	glfwTerminate();
}

inline void Window::setResizable(bool resizable) {
	glfwWindowHint(GLFW_RESIZABLE, gl_getValue(resizable));
}

inline void Window::setDecorated(bool decorated) {
	glfwWindowHint(GLFW_DECORATED, gl_getValue(decorated));
}

inline void Window::setSamples(int samples) {
	glfwWindowHint(GLFW_SAMPLES, samples);
}

inline void Window::setRefreshRate(int refreshRate) {
	glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);
}

inline void Window::setFloating(bool floating) {
	glfwWindowHint(GLFW_FLOATING, gl_getValue(floating));
}

inline void Window::setVSync(bool vSync) {
	if (vSync)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);
}

inline void Window::setPosition(int x, int y) {
	glfwSetWindowPos(m_instance, x, y);
}

inline void Window::centre() {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	setPosition(mode->width / 2 - m_settings->getWindowWidth() / 2, mode->height / 2 - m_settings->getWindowHeight() / 2);
}

inline void Window::makeCurrent() {
	glfwMakeContextCurrent(m_instance);
}

bool Window::shouldClose() {
	return gl_getBooleanValue(glfwWindowShouldClose(m_instance));
}

void Window::setKeyCallback(void (* callback)(GLFWwindow*, int , int, int, int)) {
	glfwSetKeyCallback(m_instance, callback);
}
void Window::setCharCallback(void (* callback)(GLFWwindow*, unsigned int)) {
	glfwSetCharCallback(m_instance, callback);
}
void Window::setCursorPosCallback(void (* callback)(GLFWwindow*, double, double)) {
	glfwSetCursorPosCallback(m_instance, callback);
}
void Window::setCursorEnterCallback(void (* callback)(GLFWwindow*, int)) {
	glfwSetCursorEnterCallback(m_instance, callback);
}
void Window::setMouseButtonCallback(void (* callback)(GLFWwindow*, int, int, int)) {
	glfwSetMouseButtonCallback(m_instance, callback);
}
void Window::setScrollCallback(void (* callback)(GLFWwindow*, double, double)) {
	glfwSetScrollCallback(m_instance, callback);
}

bool Window::getKey(int key) {
	int state = glfwGetKey(m_instance, key);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Window::getMouseButton(int button) {
	int state = glfwGetMouseButton(m_instance, button);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

/***************************************************************************************************/
