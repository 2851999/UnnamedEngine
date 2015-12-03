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

#include "../../Vector.h"
#include "../Shader.h"

/***************************************************************************************************
 * The BaseLight class contains information that can be found in any light source
 ***************************************************************************************************/

class BaseLight {
private:
	Colour m_colour = Colour::WHITE;
	float m_intensity = 1.0f;
public:
	BaseLight() {}
	BaseLight(Colour colour, float intensity) { m_colour = colour; m_intensity = intensity; }

	/* The setters and getters */
	inline void setColour(Colour colour) { m_colour = colour; }
	inline void setIntensity(float intensity) { m_intensity = intensity; }

	inline Colour getColour() { return m_colour; }
	inline float getIntensity() { return m_intensity; }

	void setUniforms(Shader* shader, std::string prefix);

	static void addUniforms(Shader* shader, std::string prefix, std::string location);
};

/***************************************************************************************************/

/***************************************************************************************************
 * The LightSource class is inherited by all light sources
 ***************************************************************************************************/

class LightSource {
public:
	virtual ~LightSource() {}

	virtual void apply() {}
};

/***************************************************************************************************/

/***************************************************************************************************
 * The DirectionalLight class contains information that can be found in a directional light
 ***************************************************************************************************/

class DirectionalLight : public LightSource {
private:
	BaseLight* m_baseLight;
	Vector3f m_direction;
public:
	DirectionalLight() { m_baseLight = new BaseLight(); }
	DirectionalLight(Vector3f direction) { m_baseLight = new BaseLight(); m_direction = direction; }
	DirectionalLight(BaseLight* baseLight, Vector3f direction) { m_baseLight = baseLight; m_direction = direction; }

	~DirectionalLight() {}

	/* The setters and getters */
	inline void setBaseLight(BaseLight* baseLight) { m_baseLight = baseLight; }
	inline void setDirection(Vector3f direction) { m_direction = direction; }

	inline BaseLight* getBaseLight() { return m_baseLight; }
	inline Vector3f getDirection() { return m_direction; }

	void setUniforms(Shader* shader, std::string prefix);

	void apply();

	static void addUniforms(Shader* shader, std::string prefix, std::string location);
};

/***************************************************************************************************/

/***************************************************************************************************
 * The Attenuation class contains information for the attenuation of a light source
 ***************************************************************************************************/

class Attenuation {
private:
	float m_constant = 0.0;
	float m_linear = 0.1;
	float m_exponent = 1.0;
public:
	Attenuation() {}
	Attenuation(float constant, float linear, float exponent) :
		m_constant(constant), m_linear(linear), m_exponent(exponent) {}

	/* The setters and getters */
	inline void setConstant(float constant) { m_constant = constant; }
	inline void setLinear(float linear)     { m_linear = linear; }
	inline void setExponent(float exponent) { m_exponent = exponent; }

	inline float getConstant() { return m_constant; }
	inline float getLinear()   { return m_linear; }
	inline float getExponent() { return m_exponent; }

	void setUniforms(Shader* shader, std::string prefix);

	static void addUniforms(Shader* shader, std::string prefix, std::string location);
};

/***************************************************************************************************/

/***************************************************************************************************
 * The PointLight class contains information for a Point Light
 ***************************************************************************************************/

class PointLight : public LightSource {
private:
	BaseLight*   m_baseLight;
	Attenuation  m_attenuation;
	Vector3f     m_position;
	float        m_range = 4.0f;
public:
	PointLight() { m_baseLight = new BaseLight(); }
	PointLight(Vector3f position) : m_position(position) { m_baseLight = new BaseLight(); }
	PointLight(Attenuation attenuation, Vector3f position) : m_attenuation(attenuation), m_position(position) { m_baseLight = new BaseLight(); }
	PointLight(Vector3f position, float range) : m_position(position), m_range(range) { m_baseLight = new BaseLight(); }
	PointLight(Attenuation attenuation, Vector3f position, float range) : m_attenuation(attenuation), m_position(position), m_range(range) { m_baseLight = new BaseLight(); }

	PointLight(BaseLight* baseLight) : m_baseLight(baseLight) {}
	PointLight(BaseLight* baseLight, Vector3f position) : m_baseLight(baseLight), m_position(position) {}
	PointLight(BaseLight* baseLight, Attenuation attenuation, Vector3f position) :
		m_baseLight(baseLight), m_attenuation(attenuation), m_position(position) {}
	PointLight(BaseLight* baseLight, Vector3f position, float range) : m_baseLight(baseLight), m_position(position), m_range(range) {}
	PointLight(BaseLight* baseLight, Attenuation attenuation, Vector3f position, float range) :
		m_baseLight(baseLight), m_attenuation(attenuation), m_position(position), m_range(range) {}

	~PointLight() {}

	/* The setters and getters */
	inline void setBaseLight(BaseLight* baseLight) { m_baseLight = baseLight; }
	inline void setAttenuation(Attenuation attenuation) { m_attenuation = attenuation; }
	inline void setPosition(Vector3f position) { m_position = position; }
	inline void setRange(float range) { m_range = range; }

	inline BaseLight* getBaseLight() { return m_baseLight; }
	inline Attenuation getAttenuation() { return m_attenuation; }
	inline Vector3f getPosition() { return m_position; }
	inline float getRange() { return m_range; }

	void setUniforms(Shader* shader, std::string prefix);

	void apply();

	static void addUniforms(Shader* shader, std::string prefix, std::string location);
};

/***************************************************************************************************/

/***************************************************************************************************
 * The SpotLight class contains information for a Spot Light
 ***************************************************************************************************/

class SpotLight : public LightSource {
private:
	PointLight* m_pointLight;
	Vector3f m_direction;
	float m_cutoff = 0.5f;
public:
	SpotLight() { m_pointLight = new PointLight(); }
	SpotLight(Vector3f direction) { m_pointLight = new PointLight(); m_direction = direction; }
	SpotLight(PointLight* pointLight, Vector3f direction) { m_pointLight = pointLight; m_direction = direction; }
	SpotLight(Vector3f direction, float cutoff) { m_pointLight = new PointLight(); m_direction = direction; m_cutoff = cutoff; }
	SpotLight(PointLight* pointLight, Vector3f direction, float cutoff) { m_pointLight = pointLight; m_direction = direction; m_cutoff = cutoff; }

	~SpotLight() {}

	/* The setters and getters */
	inline void setPointLight(PointLight* pointLight) { m_pointLight = pointLight; }
	inline void setDirection(Vector3f direction) { m_direction = direction; }
	inline void setCutoff(float cutoff) { m_cutoff = cutoff; }

	inline PointLight* getPointLight() { return m_pointLight; }
	inline Vector3f getDirection() { return m_direction; }
	inline float getCutoff() { return m_cutoff; }

	void setUniforms(Shader* shader, std::string prefix);

	void apply();

	static void addUniforms(Shader* shader, std::string prefix, std::string location);
};

/***************************************************************************************************/
