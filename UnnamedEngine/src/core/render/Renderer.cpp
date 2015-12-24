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
#include "../Game.h"
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
	addShader("DeferredShader", ResourceLoader::loadRenderShader("resources/shaders/deferred/", "DeferredShader", "DeferredShader"));

	DeferredRenderer::initialise();
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
	} else if (std::string(type) == "DeferredShader") {
		shader->addUniform("NormalMatrix", "nMatrix");
		shader->addUniform("ModelViewProjectionMatrix", "mvpMatrix");

		Material::addUniforms(shader);

		shader->addAttribute("Position", "position");
		shader->addAttribute("TextureCoordinate", "textureCoord");
		shader->addAttribute("Normal", "normal");
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

/***************************************************************************************************
 * The DeferredRenderer class
 ***************************************************************************************************/

/* The GBuffer */
GeometryBuffer* DeferredRenderer::m_geometryBuffer;

/* The screen quad for rendering the output */
RenderableObject2D* DeferredRenderer::m_screenQuad;

/* For debugging */
Camera2D* DeferredRenderer::m_camera;
RenderableObject2D* DeferredRenderer::m_positionQuad;
RenderableObject2D* DeferredRenderer::m_normalQuad;
RenderableObject2D* DeferredRenderer::m_colourQuad;
RenderableObject2D* DeferredRenderer::m_depthQuad;
RenderableObject2D* DeferredRenderer::m_worldPositionQuad;

void DeferredRenderer::initialise() {
	m_geometryBuffer = new GeometryBuffer();

	int width = Game::current->getSettings()->getWindowWidth();
	int height = Game::current->getSettings()->getWindowHeight();

	m_camera = new Camera2D(Matrix4f().initOrthographic(0, width, height, 0, -1, 1));
	m_camera->update();

	m_screenQuad = new RenderableObject2D(MeshBuilder::createQuad(width, height, new Texture(), Colour::WHITE));
	m_screenQuad->getMesh()->setTexture(m_geometryBuffer->getTexture(GeometryBuffer::BUFFER_COLOUR));
	m_screenQuad->setSize(width, height);
	m_screenQuad->getMesh()->getData()->clearTextureCoords();
	m_screenQuad->getMesh()->getData()->addTextureCoord(Vector2f(0, 1));
	m_screenQuad->getMesh()->getData()->addTextureCoord(Vector2f(0, 0));
	m_screenQuad->getMesh()->getData()->addTextureCoord(Vector2f(1, 0));
	m_screenQuad->getMesh()->getData()->addTextureCoord(Vector2f(1, 1));
	m_screenQuad->getMesh()->updateTextureCoords();
	m_screenQuad->update();

	m_positionQuad = new RenderableObject2D(MeshBuilder::createQuad(width / 5, height / 5, new Texture(), Colour::WHITE));
	m_positionQuad->getMesh()->setTexture(m_geometryBuffer->getTexture(GeometryBuffer::BUFFER_POSITION));
	m_positionQuad->setSize(width, height);
	m_positionQuad->getMesh()->getData()->clearTextureCoords();
	m_positionQuad->getMesh()->getData()->addTextureCoord(Vector2f(0, 1));
	m_positionQuad->getMesh()->getData()->addTextureCoord(Vector2f(0, 0));
	m_positionQuad->getMesh()->getData()->addTextureCoord(Vector2f(1, 0));
	m_positionQuad->getMesh()->getData()->addTextureCoord(Vector2f(1, 1));
	m_positionQuad->getMesh()->updateTextureCoords();
	m_positionQuad->setPosition(width - (width / 5), 0);
	m_positionQuad->update();

	m_normalQuad = new RenderableObject2D(MeshBuilder::createQuad(width / 5, height / 5, new Texture(), Colour::WHITE));
	m_normalQuad->getMesh()->setTexture(m_geometryBuffer->getTexture(GeometryBuffer::BUFFER_NORMAL));
	m_normalQuad->setSize(width, height);
	m_normalQuad->getMesh()->getData()->clearTextureCoords();
	m_normalQuad->getMesh()->getData()->addTextureCoord(Vector2f(0, 1));
	m_normalQuad->getMesh()->getData()->addTextureCoord(Vector2f(0, 0));
	m_normalQuad->getMesh()->getData()->addTextureCoord(Vector2f(1, 0));
	m_normalQuad->getMesh()->getData()->addTextureCoord(Vector2f(1, 1));
	m_normalQuad->getMesh()->updateTextureCoords();
	m_normalQuad->setPosition(width - (width / 5), (height / 5));
	m_normalQuad->update();

	m_colourQuad = new RenderableObject2D(MeshBuilder::createQuad(width / 5, height / 5, new Texture(), Colour::WHITE));
	m_colourQuad->getMesh()->setTexture(m_geometryBuffer->getTexture(GeometryBuffer::BUFFER_COLOUR));
	m_colourQuad->setSize(width, height);
	m_colourQuad->getMesh()->getData()->clearTextureCoords();
	m_colourQuad->getMesh()->getData()->addTextureCoord(Vector2f(0, 1));
	m_colourQuad->getMesh()->getData()->addTextureCoord(Vector2f(0, 0));
	m_colourQuad->getMesh()->getData()->addTextureCoord(Vector2f(1, 0));
	m_colourQuad->getMesh()->getData()->addTextureCoord(Vector2f(1, 1));
	m_colourQuad->getMesh()->updateTextureCoords();
	m_colourQuad->setPosition(width - (width / 5), (height / 5) * 2);
	m_colourQuad->update();

	m_worldPositionQuad = new RenderableObject2D(MeshBuilder::createQuad(width / 5, height / 5, new Texture(), Colour::WHITE));
	m_worldPositionQuad->getMesh()->setTexture(m_geometryBuffer->getTexture(GeometryBuffer::BUFFER_WORLD_POSITION));
	m_worldPositionQuad->setSize(width, height);
	m_worldPositionQuad->getMesh()->getData()->clearTextureCoords();
	m_worldPositionQuad->getMesh()->getData()->addTextureCoord(Vector2f(0, 1));
	m_worldPositionQuad->getMesh()->getData()->addTextureCoord(Vector2f(0, 0));
	m_worldPositionQuad->getMesh()->getData()->addTextureCoord(Vector2f(1, 0));
	m_worldPositionQuad->getMesh()->getData()->addTextureCoord(Vector2f(1, 1));
	m_worldPositionQuad->getMesh()->updateTextureCoords();
	m_worldPositionQuad->setPosition(width - (width / 5), (height / 5) * 3);
	m_worldPositionQuad->update();

	m_depthQuad = new RenderableObject2D(MeshBuilder::createQuad(width / 5, height / 5, new Texture(), Colour::WHITE));
	m_depthQuad->getMesh()->setTexture(m_geometryBuffer->getTexture(GeometryBuffer::BUFFER_DEPTH));
	m_depthQuad->setSize(width, height);
	m_depthQuad->getMesh()->getData()->clearTextureCoords();
	m_depthQuad->getMesh()->getData()->addTextureCoord(Vector2f(0, 1));
	m_depthQuad->getMesh()->getData()->addTextureCoord(Vector2f(0, 0));
	m_depthQuad->getMesh()->getData()->addTextureCoord(Vector2f(1, 0));
	m_depthQuad->getMesh()->getData()->addTextureCoord(Vector2f(1, 1));
	m_depthQuad->getMesh()->updateTextureCoords();
	m_depthQuad->setPosition(width - (width / 5), (height / 5) * 4);
	m_depthQuad->update();
}

void DeferredRenderer::renderToScreen() {
	if (m_screenQuad != NULL) {
		Renderer::addCamera(m_camera);

		m_screenQuad->render();

		if (Game::current->getSettings()->getDebuggingShowDeferredRenderingBuffers()) {
			m_positionQuad->render();
			m_normalQuad->render();
			m_colourQuad->render();
			m_worldPositionQuad->render();
			m_depthQuad->render();
		}

		Renderer::removeCamera();
	}
}

/***************************************************************************************************/
