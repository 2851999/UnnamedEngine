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

#include "DebugCamera.h"

/***************************************************************************************************
 * The DebugCamera3D class
 ***************************************************************************************************/

/* The constructor */
DebugCamera3D::DebugCamera3D(float fovy, float windowWidth, float windowHeight, float zNear, float zFar, bool lockMouse) : Camera3D(Matrix4f().initPerspective(fovy, windowWidth / windowHeight, zNear, zFar)) {
	this->lockMouse = lockMouse;

	//Lock the mouse if necessary
	if (lockMouse)
		Mouse::lock();

	//Setup the input
	addListener();
}

/* The method used to update the camera */
void DebugCamera3D::update(long delta) {
	//Clamp the rotation
	rotation.setX(clamp(rotation.getX(), minXRotation, maxXRotation));

	//The current speed
	float s = speed;
	//Update the movement
	if (Keyboard::isPressed(keyFaster))
		s = fasterSpeed;
	if (Keyboard::isPressed(keyForward))
		moveForward(s * delta);
	if (Keyboard::isPressed(keyBackward))
		moveBackward(s * delta);
	if (Keyboard::isPressed(keyLeft))
		moveLeft(s * delta);
	if (Keyboard::isPressed(keyRight))
		moveRight(s * delta);

	//Update the camera
	Camera3D::update();
}

/* The mouse moved event */
void DebugCamera3D::onMouseMoved(double x, double y, double dx, double dy) {
	if (Mouse::isLocked() || ! lockMouse)
		rotation += Vector3f(dy * mouseSensitivity, dx * mouseSensitivity, 0.0f);
}

/***************************************************************************************************/
