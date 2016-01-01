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

#ifndef CORE_CAMERA_H_
#define CORE_CAMERA_H_

#include "../utils/MathUtils.h"
#include "Object.h"
#include "SkyBox.h"

/***************************************************************************************************
 * The Camera classes provide a way to render everything from a certain point of view
 ***************************************************************************************************/

class Camera {
protected:
	/* The projection and view matrices */
	Matrix4f m_projectionMatrix;
	Matrix4f m_viewMatrix;
public:
	virtual ~Camera() {}
	/* The setters and getters */
	inline void setProjectionMatrix(Matrix4f projectionMatrix) { m_projectionMatrix = projectionMatrix; }
	inline void setViewMatrix(Matrix4f viewMatrix) { m_viewMatrix = viewMatrix; }
	inline Matrix4f getProjectionMatrix() { return m_projectionMatrix; }
	inline Matrix4f getViewMatrix() { return m_viewMatrix; }

	/* Calculates then projection view matrix and returns it */
	inline Matrix4f getProjectionViewMatrix() { return m_projectionMatrix * m_viewMatrix; }
};

class Camera2D : public Camera, public Object2D {
public:
	/* The constructors */
	Camera2D() {}
	Camera2D(Matrix4f projectionMatrix) {
		setProjectionMatrix(projectionMatrix);
		m_viewMatrix = Matrix4f();
	}
	Camera2D(Matrix4f projectionMatrix, Vector2f position) {
		setProjectionMatrix(projectionMatrix);
		setPosition(position);
		m_viewMatrix = Matrix4f();
	}
	Camera2D(Matrix4f projectionMatrix, Vector2f position, float rotation) {
		setProjectionMatrix(projectionMatrix);
		setPosition(position);
		setRotation(rotation);
		m_viewMatrix = Matrix4f();
	}
	Camera2D(Matrix4f projectionMatrix, Vector2f position, float rotation, Vector2f scale) {
		setProjectionMatrix(projectionMatrix);
		setPosition(position);
		setRotation(rotation);
		setScale(scale);
		m_viewMatrix = Matrix4f();
	}

	/* The method used to update this camera */
	void update() {
		//Reset the view matrix
		m_viewMatrix.setIdentity();
		//Transform the view matrix to represent this camera
		m_viewMatrix.transformR(getPosition(), getRotation(), getScale());
	}
};

class Camera3D : public Camera, public Object3D {
private:
	/* This skybox will be used if assigned */
	SkyBox* m_skybox;

	/* The flying value determines whether looking up allows the camera to move upwards */
	bool m_flying;
public:
	/* The constructors */
	Camera3D() { m_flying = false; m_skybox = NULL; }
	Camera3D(Matrix4f projectionMatrix) {
		setProjectionMatrix(projectionMatrix);
		m_viewMatrix = Matrix4f();
		m_flying = false;
		m_skybox = NULL;
	}
	Camera3D(Matrix4f projectionMatrix, Vector3f position) {
		setProjectionMatrix(projectionMatrix);
		setPosition(position);
		m_viewMatrix = Matrix4f();
		m_flying = false;
		m_skybox = NULL;
	}
	Camera3D(Matrix4f projectionMatrix, Vector3f position, Vector3f rotation) {
		setProjectionMatrix(projectionMatrix);
		setPosition(position);
		setRotation(rotation);
		m_viewMatrix = Matrix4f();
		m_flying = false;
		m_skybox = NULL;
	}
	Camera3D(Matrix4f projectionMatrix, Vector3f position, Vector3f rotation, Vector3f scale) {
		setProjectionMatrix(projectionMatrix);
		setPosition(position);
		setRotation(rotation);
		setScale(scale);
		m_viewMatrix = Matrix4f();
		m_flying = false;
		m_skybox = NULL;
	}

	/* The update method */
	void update() {
		//Reset the view matrix
		m_viewMatrix.setIdentity();
		//Transform the view matrix to represent this camera
		m_viewMatrix.transformR(getPosition(), getRotation(), getScale());
	}

	/* This method will render the skybox if assigned */
	void useView() {
		if (m_skybox != NULL) {
			m_skybox->update(getPosition());
			m_skybox->render();
		}
	}

	/* Moves the camera forward in the direction it is facing */
	void moveForward(float amount) {
		position.setX(position.getX() - clamp(amount * (float) sin(to_radians(rotation.getY())), -amount, amount));
		position.setZ(position.getZ() + clamp(amount * (float) cos(to_radians(rotation.getY())), -amount, amount));
		if (m_flying)
			position.setY(position.getY() + clamp(amount * (float) tan(to_radians(rotation.getX())), -amount, amount));
	}

	/* Moves the camera backward in the direction it is facing */
	void moveBackward(float amount) {
		position.setX(position.getX() + clamp(amount * (float) sin(to_radians(rotation.getY())), -amount, amount));
		position.setZ(position.getZ() - clamp(amount * (float) cos(to_radians(rotation.getY())), -amount, amount));
		if (m_flying)
			position.setY(position.getY() - clamp(amount * (float) tan(to_radians(rotation.getX())), -amount, amount));
	}

	/* Moves the camera left in the direction it is facing */
	void moveLeft(float amount) {
		position.setX(position.getX() - clamp(amount * (float) sin(to_radians(rotation.getY() - 90)), -amount, amount));
		position.setZ(position.getZ() + clamp(amount * (float) cos(to_radians(rotation.getY() - 90)), -amount, amount));
	}

	/* Moves the camera right in the direction it is facing */
	void moveRight(float amount) {
		position.setX(position.getX() + clamp(amount * (float) sin(to_radians(rotation.getY() - 90)), -amount, amount));
		position.setZ(position.getZ() - clamp(amount * (float) cos(to_radians(rotation.getY() - 90)), -amount, amount));
	}

	/* The setters and getters */
	inline void setFlying(bool flying) { m_flying = flying; }
	inline void toggleFlying() { m_flying = !m_flying; }
	inline bool isFlying() { return m_flying; }
	inline void setSkyBox(SkyBox* skybox) { m_skybox = skybox; }
	inline SkyBox* getSkyBox() { return m_skybox; }
};

/***************************************************************************************************/

#endif /* CORE_CAMERA_H_ */
