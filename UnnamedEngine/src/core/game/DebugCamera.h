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

#ifndef CORE_GAME_DEBUGCAMERA_H_
#define CORE_GAME_DEBUGCAMERA_H_

#include "../Camera.h"
#include "../input/Input.h"

/***************************************************************************************************
 * The DebugCamera3D class
 ***************************************************************************************************/

class DebugCamera3D : public Camera3D, InputListener {

public:
	/* The movement keys */
	int keyForward   = GLFW_KEY_W;
	int keyBackward  = GLFW_KEY_S;
	int keyLeft      = GLFW_KEY_A;
	int keyRight     = GLFW_KEY_D;
	int keyFaster    = GLFW_KEY_LEFT_SHIFT;

	/* The speeds */
	float speed            = 0.01f;
	float fasterSpeed      = 0.05f;
	float mouseSensitivity = 0.5f;

	/* The values to clamp to for the x rotation (looking up and down */
	float minXRotation     = -80;
	float maxXRotation     = 80;

	/* States whether the mouse should be locked */
	bool lockMouse;

	/* The constructor */
	DebugCamera3D(float fovy, float windowWidth, float windowHeight, float zNear, float zFar, bool lockMouse = true);

	/* The update method */
	void update(long delta);

	/* The input methods */
	void onKeyPressed(int code) {}
	void onKeyReleased(int code) {}
	void onKeyTyped(int code) {}
	void onChar(int code, char character) {}

	void onMousePressed(int button) {}
	void onMouseReleased(int button) {}
	void onMouseClicked(int button) {}
	void onMouseMoved(double x, double y, double dx, double dy);
	void onMouseDragged(double x, double y, double dx, double dy) {}
	void onMouseEnter() {}
	void onMouseLeave() {}

	virtual void onScroll(double dx, double dy) {}
};

/***************************************************************************************************/

#endif /* CORE_GAME_DEBUGCAMERA_H_ */
