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

#ifndef CORE_RENDER_MATERIAL_H_
#define CORE_RENDER_MATERIAL_H_

#include "Shader.h"
#include "../Vector.h"
#include "../Texture.h"

/***************************************************************************************************
 * The Material class stores data about a material
 ***************************************************************************************************/

class Material {
private:
	Colour m_ambientColour = Colour::WHITE;
	Colour m_diffuseColour = Colour::WHITE;
	Colour m_specularColour = Colour::WHITE;
	Texture* m_diffuseTexture;
	Texture* m_specularTexture;
	Texture* m_normalMap;
	float m_shininess = 0.0;
public:
	Material() { m_diffuseTexture = NULL; m_specularTexture = NULL; m_normalMap = NULL; }
	inline void setAmbientColour(Colour colour) { m_ambientColour = colour; }
	inline void setDiffuseColour(Colour colour) { m_diffuseColour = colour; }
	inline void setSpecularColour(Colour colour) { m_specularColour = colour; }
	inline void setDiffuseTexture(Texture* texture) { m_diffuseTexture = texture; }
	inline void setSpecularTexture(Texture* texture) { m_specularTexture = texture; }
	inline void setNormalMap(Texture* texture) { m_normalMap = texture; }
	inline void setShininess(float shininess) { m_shininess = shininess; }
	inline Colour getAmbientColour() { return m_ambientColour; }
	inline Colour getDiffuseColour() { return m_diffuseColour; }
	inline Colour getSpecularColour() { return m_specularColour; }
	inline Texture* getDiffuseTexture() { return m_diffuseTexture; }
	inline Texture* getSpecularTexture() { return m_specularTexture; }
	inline Texture* getNormalMap() { return m_normalMap; }
	inline bool hasDiffuseTexture() { return m_diffuseTexture != NULL; }
	inline bool hasSpecularTexture() { return m_specularTexture != NULL; }
	inline bool hasNormalMap() { return m_normalMap != NULL; }
	inline float getShininess() { return m_shininess; }

	void setUniforms(Shader* shader);
	static void addUniforms(Shader* shader);
};

/***************************************************************************************************/

#endif /* CORE_RENDER_MATERIAL_H_ */
