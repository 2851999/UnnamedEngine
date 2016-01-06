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

#ifndef CORE_PHYSICS_PHYSICSOBJECT_H_
#define CORE_PHYSICS_PHYSICSOBJECT_H_

#include "../Object.h"

/***************************************************************************************************
 * The PhysicsObject class
 ***************************************************************************************************/

class PhysicsObject {
public:
	PhysicsObject() {}
	virtual ~PhysicsObject() {}

	/* The method used to update this physics object */
	virtual void update(float delta) {}
};

/***************************************************************************************************/

/***************************************************************************************************
 * The PhysicsObject2D class
 ***************************************************************************************************/

class PhysicsObject2D : public PhysicsObject {
private:
	/* The object */
	Object2D* m_object;
public:
	/* The various physics related values */
	Vector2f velocity;
	Vector2f acceleration;
	float angularVelocity = 0;
	float angularAcceleration = 0;
	float mass = 0;

	/* The constructor */
	PhysicsObject2D(Object2D* object) : m_object(object) {}

	/* The method used to update this physics object */
	void update(float delta) override;

	/* The method used to apply a force on this object */
	void applyForce(Vector2f force);

	/* The setters and getters */
	inline void setObject(Object2D* object) { m_object = object; }
	inline void setVelocity(Vector2f velocity) { this->velocity = velocity; }
	inline void setVelocity(float x, float y) { velocity = Vector2f(x, y); }
	inline void setAcceleration(Vector2f acceleration) { this->acceleration = acceleration; }
	inline void setAcceleration(float x, float y) { acceleration = Vector2f(x, y); }
	inline void setAngularVelocity(float angularVelocity) { this->angularVelocity = angularVelocity; }
	inline void setAngularAcceleration(float angularAcceleration) { this->angularAcceleration = angularAcceleration; }
	inline void setMass(float mass) { this->mass = mass; }
	inline Object2D* getObject() { return m_object; }
	inline Vector2f getVelocity() { return velocity; }
	inline Vector2f getAcceleration() { return acceleration; }
	inline float getAngularVelocity() { return angularVelocity; }
	inline float getAngularAcceleration() { return angularAcceleration; }
	inline float getMass() { return mass; }
};

/***************************************************************************************************/

/***************************************************************************************************
 * The PhysicsObject3D class
 ***************************************************************************************************/

class PhysicsObject3D : public PhysicsObject {
private:
	/* The object */
	Object3D* m_object;
public:
	/* The various physics related values */
	Vector3f velocity;
	Vector3f acceleration;
	Vector3f angularVelocity;
	Vector3f angularAcceleration;
	float mass = 0;

	/* The constructor */
	PhysicsObject3D(Object3D* object) : m_object(object) {}

	/* The method used to update this physics object */
	void update(float delta) override;

	/* The method used to apply a force on this object */
	void applyForce(Vector3f force);

	/* The setters and getters */
	inline void setObject(Object3D* object) { m_object = object; }
	inline void setVelocity(Vector3f velocity) { this->velocity = velocity; }
	inline void setVelocity(float x, float y, float z) { velocity = Vector3f(x, y, z); }
	inline void setAcceleration(Vector3f acceleration) { this->acceleration = acceleration; }
	inline void setAcceleration(float x, float y, float z) { acceleration = Vector3f(x, y, z); }
	inline void setAngularVelocity(Vector3f angularVelocity) { this->angularVelocity = angularVelocity; }
	inline void setAngularVelocity(float x, float y, float z) { angularVelocity = Vector3f(x, y, z); }
	inline void setAngularAcceleration(Vector3f angularAcceleration) { this->angularAcceleration = angularAcceleration; }
	inline void setAngularAcceleration(float x, float y, float z) { angularAcceleration = Vector3f(x, y, z); }
	inline void setMass(float mass) { this->mass = mass; }
	inline Object3D* getObject() { return m_object; }
	inline Vector3f getVelocity() { return velocity; }
	inline Vector3f getAcceleration() { return acceleration; }
	inline Vector3f getAngularVelocity() { return angularVelocity; }
	inline Vector3f getAngularAcceleration() { return angularAcceleration; }
	inline float getMass() { return mass; }
};

/***************************************************************************************************/

#endif /* CORE_PHYSICS_PHYSICSOBJECT_H_ */
