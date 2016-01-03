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

#ifndef CORE_RENDER_SCENE_H_
#define CORE_RENDER_SCENE_H_

#include <algorithm>

#include "lighting/Light.h"
#include "../Object.h"

/***************************************************************************************************
 * The Scene class will be able to store pointers to all of the objects found in a particular scene
 * allowing effects such as lighting and shadows to be applied more easily
 ***************************************************************************************************/

class Scene {
private:
	std::vector<RenderableObject*> m_objects;
	std::vector<LightSource*> m_lights;

	bool m_lightingEnabled = true;
	Colour m_ambientLight = Colour(0.1, 0.1, 0.1, 1.0);
	float m_specularIntensity = 0.2f;
public:
	virtual ~Scene() {}

	inline void add(RenderableObject* object) { m_objects.push_back(object); }
	inline void add(LightSource* light) { m_lights.push_back(light); }
	inline void remove(RenderableObject* object) { m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end()); }
	inline void remove(LightSource* light) { m_lights.erase(std::remove(m_lights.begin(), m_lights.end(), light), m_lights.end()); }

	void update();
	void render(Vector3f cameraPosition);
	void renderFinal(Vector3f cameraPosition); //For deferred rendering

	/* The setters and getters */
	inline void setLightingEnabled(bool lightingEnabled) { m_lightingEnabled = lightingEnabled; }
	inline void setAmbientLight(Colour ambientLight) { m_ambientLight = ambientLight; }
	inline void setSpecularIntensity(float specularIntensity) { m_specularIntensity = specularIntensity; }

	inline unsigned int getNumObjects() { return m_objects.size(); }
	inline unsigned int getNumLights() { return m_lights.size(); }
	inline RenderableObject* getObject(unsigned int n) { return m_objects.at(n); }
	inline LightSource* getLight(unsigned int n) { return m_lights.at(n); }

	inline bool isLightingEnabled() { return m_lightingEnabled; }
	inline Colour getAmbientLight() { return m_ambientLight; }
	inline float getSpecularIntensity() { return m_specularIntensity; }
};

/***************************************************************************************************/

#endif /* CORE_RENDER_SCENE_H_ */
