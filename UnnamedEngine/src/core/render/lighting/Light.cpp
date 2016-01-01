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

#include "Light.h"
#include "../Renderer.h"

/***************************************************************************************************
 * The BaseLight class
 ***************************************************************************************************/

void BaseLight::addUniforms(Shader* shader, std::string prefix, std::string location) {
	shader->addUniform(prefix + "BaseLight_Colour", location + "colour");
	shader->addUniform(prefix + "BaseLight_Intensity", location + "intensity");
}

void BaseLight::setUniforms(Shader* shader, std::string prefix) {
	shader->setUniform(prefix + "BaseLight_Colour", Vector3f(m_colour.getR(), m_colour.getG(), m_colour.getB()));
	shader->setUniform(prefix + "BaseLight_Intensity", m_intensity);
}

/***************************************************************************************************/

/***************************************************************************************************
 * The DirectionalLight class
 ***************************************************************************************************/

void DirectionalLight::addUniforms(Shader* shader, std::string prefix, std::string location) {
	shader->addUniform(prefix + "DirectionalLight_Direction", location + "direction");

	BaseLight::addUniforms(shader, prefix + "DirectionalLight_", location + "base.");
}

void DirectionalLight::setUniforms(Shader* shader, std::string prefix) {
	shader->setUniform(prefix + "DirectionalLight_Direction", m_direction);

	m_baseLight->setUniforms(shader, prefix + "DirectionalLight_");
}

void DirectionalLight::apply() {
	Shader* shader = Renderer::getShader("DirectionalLight");
	shader->use();
	Renderer::setShader(shader);
	setUniforms(shader, "");
}

/***************************************************************************************************/

/***************************************************************************************************
 * The Attenuation class
 ***************************************************************************************************/

void Attenuation::addUniforms(Shader* shader, std::string prefix, std::string location) {
	shader->addUniform(prefix + "Attenuation_Constant", location + "constant");
	shader->addUniform(prefix + "Attenuation_Linear", location + "linear");
	shader->addUniform(prefix + "Attenuation_Exponent", location + "exponent");
}

void Attenuation::setUniforms(Shader* shader, std::string prefix) {
	shader->setUniform(prefix + "Attenuation_Constant", m_constant);
	shader->setUniform(prefix + "Attenuation_Linear", m_linear);
	shader->setUniform(prefix + "Attenuation_Exponent", m_exponent);
}

/***************************************************************************************************/

/***************************************************************************************************
 * The PointLight class
 ***************************************************************************************************/

void PointLight::addUniforms(Shader* shader, std::string prefix, std::string location) {
	shader->addUniform(prefix + "PointLight_Position", location + "position");
	shader->addUniform(prefix + "PointLight_Range", location + "range");

	BaseLight::addUniforms(shader, prefix + "PointLight_", location + "base.");
	Attenuation::addUniforms(shader, prefix + "PointLight_", location + "attenuation.");
}

void PointLight::setUniforms(Shader* shader, std::string prefix) {
	shader->setUniform(prefix + "PointLight_Position", m_position);
	shader->setUniform(prefix + "PointLight_Range", m_range);

	m_baseLight->setUniforms(shader, prefix + "PointLight_");
	m_attenuation.setUniforms(shader, prefix + "PointLight_");
}

void PointLight::apply() {
	Shader* shader = Renderer::getShader("PointLight");
	shader->use();
	Renderer::setShader(shader);
	setUniforms(shader, "");
}

/***************************************************************************************************/

/***************************************************************************************************
 * The SpotLight class
 ***************************************************************************************************/

void SpotLight::addUniforms(Shader* shader, std::string prefix, std::string location) {
	shader->addUniform(prefix + "SpotLight_Direction", location + "direction");
	shader->addUniform(prefix + "SpotLight_Cutoff", location + "cutoff");

	PointLight::addUniforms(shader, prefix + "SpotLight_", location + "pointLight.");
}

void SpotLight::setUniforms(Shader* shader, std::string prefix) {
	shader->setUniform(prefix + "SpotLight_Direction", m_direction);
	shader->setUniform(prefix + "SpotLight_Cutoff", m_cutoff);

	m_pointLight->setUniforms(shader, prefix + "SpotLight_");
}

void SpotLight::apply() {
	Shader* shader = Renderer::getShader("SpotLight");
	shader->use();
	Renderer::setShader(shader);
	setUniforms(shader, "");
}

/***************************************************************************************************/
