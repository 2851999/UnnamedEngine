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

#ifndef CORE_OBJECT_H_
#define CORE_OBJECT_H_

#include "../utils/MathUtils.h"
#include "Vector.h"
#include "Matrix.h"
#include "Mesh.h"
#include "Rectangle.h"

/***************************************************************************************************
 * The Object2D and 3D classes store data about 2D and 3D objects
 ***************************************************************************************************/
class Object {
public:
	void update() {}
	void render() {}
};

class Object2D : public Object {
private:
	Object2D* m_parent = NULL;
public:
	Vector2f position;
	float    rotation;
	Vector2f scale;
	Vector2f size;
	Object2D() {
		position = Vector2f();
		rotation = 0;
		scale = Vector2f(1, 1);
		size = Vector2f();
	}
	Object2D(Vector2f position) : position(position) {
		rotation = 0;
		scale = Vector2f(1, 1);
		size = Vector2f();
	}
	Object2D(Vector2f position, float rotation) : position(position), rotation(rotation) {
		scale = Vector2f(1, 1);
		size = Vector2f();
	}
	Object2D(Vector2f position, float rotation, Vector2f scale) : position(position), rotation(rotation), scale(scale) {
		size = Vector2f();
	}
	Object2D(Vector2f position, Vector2f size) : position(position), size(size) {
		rotation = 0;
		scale = Vector2f();
	}
	Object2D(Vector2f position, Vector2f scale, Vector2f size) : position(position), scale(scale), size(size) {
		rotation = 0;
	}
	Object2D(Vector2f position, float rotation, Vector2f scale, Vector2f size) : position(position), rotation(rotation), scale(scale), size(size) {}


	inline void setPosition(Vector2f position) { this->position = position; }
	inline void setPosition(float x, float y) { position = Vector2f(x, y); }
	inline void setRotation(float rotation) { this->rotation = rotation; }
	inline void setScale(Vector2f scale) { this->scale = scale; }
	inline void setScale(float x, float y) { scale = Vector2f(x, y); }
	inline void setScale(float value) { scale = Vector2f(value, value); }
	inline void setSize(Vector2f size) { this->size = size; }
	inline void setSize(float width, float height) { size = Vector2f(width, height); }
	inline void setWidth(float width) { size.setX(width); }
	inline void setHeight(float height) { size.setY(height); }
	inline Vector2f getPosition() {
		if (m_parent == NULL)
			return position;
		else
			return m_parent->getPosition() + position;
	}
	inline float getRotation() {
		if (m_parent == NULL)
			return rotation;
		else
			return m_parent->getRotation() + rotation;
	}
	inline Vector2f getScale()    {
		if (m_parent == NULL)
			return scale;
		else
			return m_parent->getScale() * scale;
	}
	inline Vector2f getSize() {
		return size * getScale();
	}
	inline float getWidth() { return size.getX() * getScale().getX(); }
	inline float getHeight() { return size.getY() * getScale().getY(); }

	inline Vector2f getCentre() { return getPosition() + (getSize() / 2); }

	Rect getBounds() {
		Vector2f p = getPosition();
		return Rect(p.getX(), p.getY(), getWidth(), getHeight());
	}

	inline void setParent(Object2D* parent) { m_parent = parent; }
	inline Object2D* getParent() { return m_parent; }
	inline void attach(Object2D* child) { child->setParent(this); }
};

class Object3D : public Object {
private:
	Object3D* m_parent = NULL;
public:
	Vector3f position;
	Vector3f rotation;
	Vector3f scale;
	Vector3f size;
	Object3D() {
		position = Vector3f();
		rotation = 0;
		scale = Vector3f(1, 1, 1);
		size = Vector3f();
	}
	Object3D(Vector3f position) : position(position) {
		rotation = 0;
		scale = Vector3f(1, 1, 1);
		size = Vector3f();
	}
	Object3D(Vector3f position, Vector3f rotation) : position(position), rotation(rotation) {
		scale = Vector3f(1, 1, 1);
		size = Vector3f();
	}
	Object3D(Vector3f position, Vector3f rotation, Vector3f scale) : position(position), rotation(rotation), scale(scale) {
		size = Vector3f();
	}
	Object3D(Vector3f position, Vector3f rotation, Vector3f scale, Vector3f size) : position(position), rotation(rotation), scale(scale), size(size) {}


	inline void setPosition(Vector3f position) { this->position = position; }
	inline void setPosition(float x, float y, float z) { position = Vector3f(x, y, z); }
	inline void setRotation(Vector3f rotation) { this->rotation = rotation; }
	inline void setRotation(float x, float y, float z) { rotation = Vector3f(x, y, z); }
	inline void setScale(Vector3f scale) { this->scale = scale; }
	inline void setScale(float x, float y, float z) { scale = Vector3f(x, y, z); }
	inline void setScale(float value) { scale = Vector3f(value, value, value); }
	inline void setSize(Vector3f size) { this->size = size; }
	inline void setSize(float width, float height, float depth) { size = Vector3f(width, height, depth); }
	inline void setWidth(float width) { size.setX(width); }
	inline void setHeight(float height) { size.setY(height); }
	inline void setDepth(float depth) { size.setZ(depth); }
	inline Vector3f getPosition() {
		if (m_parent == NULL)
			return position;
		else
			return m_parent->getPosition() + position;
	}
	inline Vector3f getRotation() {
		if (m_parent == NULL)
			return rotation;
		else
			return m_parent->getRotation() + rotation;
	}
	inline Vector3f getScale()    {
		if (m_parent == NULL)
			return scale;
		else
			return m_parent->getScale() * scale;
	}
	inline Vector3f getSize() {
		return size * getScale();
	}
	inline float getWidth() { return size.getX() * getScale().getX(); }
	inline float getHeight() { return size.getY() * getScale().getY(); }
	inline float getDepth() { return size.getZ() * getScale().getZ(); }

	inline Vector3f getCentre() { return getPosition() + (getSize() / 2); }

	inline void setParent(Object3D* parent) { m_parent = parent; }
	inline Object3D* getParent() { return m_parent; }
	inline void attach(Object3D* child) { child->setParent(this); }
};

/***************************************************************************************************/

/***************************************************************************************************
 * The renderable object classes store data about 2D and 3D objects for them to be rendered
 ***************************************************************************************************/

class RenderableObject2D : public Object2D {
private:
	Mesh* m_mesh;
	Matrix4f m_modelMatrix;
public:
	RenderableObject2D() { m_mesh = NULL; }
	RenderableObject2D(Mesh* mesh) : m_mesh(mesh) {
		m_modelMatrix = Matrix4f();
	}
	RenderableObject2D(Mesh* mesh, Vector2f size) : m_mesh(mesh) {
		setSize(size);
		m_modelMatrix = Matrix4f();
	}

	RenderableObject2D(Mesh* mesh, float width, float height) : m_mesh(mesh) {
		setSize(width, height);
		m_modelMatrix = Matrix4f();
	}
	virtual ~RenderableObject2D() {}

	void update() {
		m_modelMatrix.setIdentity();
		Vector2f p = getPosition();
		float w = getWidth() / 2;
		float h = getHeight() / 2;
		m_modelMatrix.translate(Vector2f(w, h) + p);
		//m_modelMatrix.translate(p);
		m_modelMatrix.rotate(getRotation());
		m_modelMatrix.translate(Vector2f(-w, -h));
		m_modelMatrix.scale(getScale());
	}

	virtual void render();

	inline Mesh* getMesh() { return m_mesh; }
	inline Matrix4f getModelMatrix() { return m_modelMatrix; }
};

class RenderableObject3D : public Object3D {
private:
	Mesh* m_mesh;
	Matrix4f m_modelMatrix;
public:
	RenderableObject3D() { m_mesh = NULL; }
	RenderableObject3D(Mesh* mesh) : m_mesh(mesh) {
		m_modelMatrix = Matrix4f();
	}
	RenderableObject3D(Mesh* mesh, Vector3f size) : m_mesh(mesh) {
		setSize(size);
		m_modelMatrix = Matrix4f();
	}
	RenderableObject3D(Mesh* mesh, float width, float height, float depth) : m_mesh(mesh) {
		setSize(width, height, depth);
		m_modelMatrix = Matrix4f();
	}
	virtual ~RenderableObject3D() {}

	void update() {
		m_modelMatrix.setIdentity();
		Vector3f p = getPosition();
		float w = getWidth() / 2;
		float h = getHeight() / 2;
		float d = getDepth() / 2;
		m_modelMatrix.translate(Vector3f(p.getX() + w, p.getY() + h, p.getZ() + d));
		//m_modelMatrix.translate(p);
		m_modelMatrix.rotate(getRotation());
		m_modelMatrix.translate(Vector3f(-w, -h, -d));
		m_modelMatrix.scale(getScale());
	}

	virtual void render();

	inline Mesh* getMesh() { return m_mesh; }
	inline Matrix4f getModelMatrix() { return m_modelMatrix; }
};

/***************************************************************************************************/

#endif /* CORE_OBJECT_H_ */
