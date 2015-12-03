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

#include "Material.h"
#include "Renderer.h"

/***************************************************************************************************
 * The Material class
 ***************************************************************************************************/

void Material::addUniforms(Shader* shader) {
	shader->addUniform("Material_AmbientColour", "material.ambientColour");
	shader->addUniform("Material_DiffuseColour", "material.diffuseColour");
	shader->addUniform("Material_SpecularColour", "material.specularColour");
	shader->addUniform("Material_DiffuseTexture", "material.diffuseTexture");
	shader->addUniform("Material_SpecularTexture", "material.specularTexture");
	shader->addUniform("Material_Shininess", "material.shininess");
}

void Material::setUniforms(Shader* shader) {
	shader->setUniform("Material_AmbientColour", m_ambientColour);
	shader->setUniform("Material_DiffuseColour", m_diffuseColour);
	shader->setUniform("Material_SpecularColour", m_specularColour);

	if (m_diffuseTexture == NULL)
		shader->setUniform("Material_DiffuseTexture", Renderer::bindTexture(Renderer::TEXTURE_BLANK));
	else
		shader->setUniform("Material_DiffuseTexture", Renderer::bindTexture(m_diffuseTexture));

	shader->setUniform("Material_SpecularTexture", 0); //Will need to change this

	shader->setUniform("Material_Shininess", m_shininess);
}

/***************************************************************************************************/
