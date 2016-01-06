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

#include "PhysicsObject.h"

/***************************************************************************************************
 * The PhysicsObject2D class
 ***************************************************************************************************/

void PhysicsObject2D::update(float delta) {
	//Apply the acceleration
	velocity += acceleration * delta;
	angularVelocity += angularAcceleration * delta;

	//Apply the velocity
	m_object->position += velocity * delta;
	m_object->rotation += angularVelocity * delta;
}

void PhysicsObject2D::applyForce(Vector2f force) {
	if (mass != 0)
		velocity += force / mass;
}

/***************************************************************************************************/

/***************************************************************************************************
 * The PhysicsObject3D class
 ***************************************************************************************************/

void PhysicsObject3D::update(float delta) {
	//Apply the acceleration
	velocity += acceleration * delta;
	angularVelocity += angularAcceleration * delta;

	//Apply the velocity
	m_object->position += velocity * delta;
	m_object->rotation += angularVelocity * delta;
}

void PhysicsObject3D::applyForce(Vector3f force) {
	if (mass != 0)
		velocity += force / mass;
}

/***************************************************************************************************/
