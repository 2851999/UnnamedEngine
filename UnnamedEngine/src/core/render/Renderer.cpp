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

#include "../../utils/FileUtils.h"
#include "../ResourceLoader.h"
#include "lighting/Light.h"

#include "Renderer.h"

/***************************************************************************************************
 * The Renderer class is responsible for rendering
 ***************************************************************************************************/
std::vector<Camera*> Renderer::m_cameras;
std::map<std::string, RenderShader*> Renderer::m_shaders;

Texture* Renderer::TEXTURE_BLANK;

std::vector<Texture*> Renderer::m_boundTextures;

Shader* Renderer::m_overrideShader;

void Renderer::render(Mesh* mesh, Matrix4f modelMatrix, std::string shaderType) {
	Shader* currentShader = getShader(shaderType);
	if (currentShader != NULL) {
		Matrix4f mvp = (getCamera()->getProjectionViewMatrix() * modelMatrix).transpose();
		currentShader->use();
		if (mesh->getRenderData()->hasMaterial()) {
			mesh->getRenderData()->getMaterial()->setUniforms(currentShader);
		} else {
			if (mesh->hasTexture())
				glUniform1i(currentShader->getUniformLocation("Texture"), Renderer::bindTexture(mesh->getTexture()));
			else
				glUniform1i(currentShader->getUniformLocation("Texture"), Renderer::bindTexture(TEXTURE_BLANK));
		}
		glUniformMatrix4fv(currentShader->getUniformLocation("ModelViewProjectionMatrix"), 1, GL_FALSE, &(mvp.m_values[0][0]));
		mesh->render();
		currentShader->stopUsing();
		Renderer::unbindTetxures();
	}
}

void Renderer::initialise() {
	//Initialise the textures
	TEXTURE_BLANK = Texture::loadTexture("resources/textures/blank.png");

	//Add the shaders
	addShader("Basic", ResourceLoader::loadRenderShader("resources/shaders/", "BasicShader", "Basic"));
	addShader("SkyBox", ResourceLoader::loadRenderShader("resources/shaders/", "SkyBoxShader", "SkyBox"));
	addShader("Material", ResourceLoader::loadRenderShader("resources/shaders/", "MaterialShader", "Material"));
	addShader("DirectionalLight", ResourceLoader::loadRenderShader("resources/shaders/lighting/", "DirectionalLight", "DirectionalLight"));
	addShader("PointLight", ResourceLoader::loadRenderShader("resources/shaders/lighting/", "PointLight", "PointLight"));
	addShader("SpotLight", ResourceLoader::loadRenderShader("resources/shaders/lighting/", "SpotLight", "SpotLight"));
	addShader("AmbientLight", ResourceLoader::loadRenderShader("resources/shaders/lighting/", "AmbientLight", "AmbientLight"));
}

void Renderer::setupShader(Shader* shader, const char* type) {
	if (std::string(type) == "Basic") {
		shader->addUniform("ModelViewProjectionMatrix", "mvpMatrix");
		shader->addUniform("Texture", "tex");
		shader->addAttribute("Position", "position");
		shader->addAttribute("Colour", "colour");
		shader->addAttribute("TextureCoordinate", "textureCoord");
	} else if (std::string(type) == "Material") {
		shader->addUniform("ModelViewProjectionMatrix", "mvpMatrix");
		shader->addAttribute("Position", "position");
		shader->addAttribute("Colour", "colour");
		shader->addAttribute("TextureCoordinate", "textureCoord");

		Material::addUniforms(shader);
	} else if (std::string(type) == "SkyBox") {
		shader->addUniform("ModelViewProjectionMatrix", "mvpMatrix");
		shader->addUniform("Texture", "tex");
		shader->addAttribute("Position", "position");
	} else if (std::string(type).find("Light") != std::string::npos) {
		shader->addUniform("NormalMatrix", "nMatrix");
		shader->addUniform("ModelViewProjectionMatrix", "mvpMatrix");

		shader->addUniform("AmbientLight", "ambientLight");
		shader->addUniform("SpecularIntensity", "specularIntensity");
		shader->addUniform("EyePosition", "eyePosition");

		Material::addUniforms(shader);

		shader->addAttribute("Position", "position");
		shader->addAttribute("TextureCoordinate", "textureCoord");
		shader->addAttribute("Normal", "normal");

		if (std::string(type) == "DirectionalLight") {
			DirectionalLight::addUniforms(shader, "", "directionalLight.");
		} else if (std::string(type) == "PointLight") {
			PointLight::addUniforms(shader, "", "pointLight.");
		} else if (std::string(type) == "SpotLight") {
			SpotLight::addUniforms(shader, "", "spotLight.");
		}
	} else {
		logError("Unknown shader type '" + to_string(type) + "'");
	}
}

GLuint Renderer::bindTexture(Texture* texture) {
	glActiveTexture(GL_TEXTURE0 + m_boundTextures.size());
	texture->bind();
	m_boundTextures.push_back(texture);

	return m_boundTextures.size() - 1;
}

void Renderer::unbindTetxures() {
	while (m_boundTextures.size() > 0) {
		glActiveTexture(GL_TEXTURE0 + m_boundTextures.size());
		m_boundTextures.at(m_boundTextures.size() - 1)->unbind();
		m_boundTextures.pop_back();
	}
}

/***************************************************************************************************/
