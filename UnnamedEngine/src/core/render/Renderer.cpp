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

#include "../../utils/FileUtils.h"
#include "../ResourceLoader.h"
#include "lighting/Light.h"

#include "Renderer.h"
#include "../BaseEngine.h"

/***************************************************************************************************
 * The Renderer class is responsible for rendering
 ***************************************************************************************************/
std::vector<Camera*> Renderer::m_cameras;
std::map<std::string, RenderShader*> Renderer::m_shaders;

Texture* Renderer::TEXTURE_BLANK;

std::vector<Texture*> Renderer::m_boundTextures;

Shader* Renderer::m_overrideShader;

bool Renderer::m_deferredRendering;

void Renderer::render(Mesh* mesh, Matrix4f modelMatrix, std::string shaderType) {
	Shader* currentShader = getShader(shaderType);
	if (currentShader != NULL) {
		Matrix4f mvp = (getCamera()->getProjectionViewMatrix() * modelMatrix).transpose();
		currentShader->use();
		if (mesh->getRenderData()->hasMaterial()) {
			mesh->getRenderData()->getMaterial()->setUniforms(currentShader);
		} else {
			if (mesh->hasTexture()) {
				glUniform1i(currentShader->getUniformLocation("Texture"), Renderer::bindTexture(mesh->getTexture()));
			} else
				glUniform1i(currentShader->getUniformLocation("Texture"), Renderer::bindTexture(TEXTURE_BLANK));
		}
		glUniformMatrix4fv(currentShader->getUniformLocation("ModelViewProjectionMatrix"), 1, GL_FALSE, &(mvp.m_values[0][0]));
		mesh->render();
		currentShader->stopUsing();
		Renderer::unbindTetxures();
	}
}

void Renderer::initialise() {
	//Initialise GLFW
	GLenum status = glewInit();
	if (status)
		logError("GLEW initialisation failed");

	//Initialise the textures
	TEXTURE_BLANK = Texture::loadTexture("resources/textures/blank.png");

	m_deferredRendering = false;

	//Initialise the shaders
	initialiseShaders();

	DeferredRenderer::initialise();
}

void Renderer::initialiseShaders() {
	//Remove any existing shaders
	if (m_shaders.size() > 0) {
		for (std::map<std::string, RenderShader*>::iterator it = m_shaders.begin(); it != m_shaders.end(); it++)
			delete it->second;
		m_shaders.clear();
	}

	//Add the shaders
	addShader("ForwardBasic", ResourceLoader::loadRenderShader("resources/shaders/", "ForwardBasicShader", "ForwardBasic"));
	addShader("DeferredBasic", ResourceLoader::loadRenderShader("resources/shaders/", "DeferredBasicShader", "DeferredBasic"));
	addShader("Material", ResourceLoader::loadRenderShader("resources/shaders/", "MaterialShader", "Material"));
	addShader("SkyBox", ResourceLoader::loadRenderShader("resources/shaders/", "SkyBoxShader", "SkyBox"));

	addShader("ForwardAmbientLight", ResourceLoader::loadRenderShader("resources/shaders/lighting/", "ForwardAmbientLight", "ForwardAmbientLight"));
	addShader("ForwardDirectionalLight", ResourceLoader::loadRenderShader("resources/shaders/lighting/", "ForwardDirectionalLight", "ForwardDirectionalLight"));
	addShader("ForwardPointLight", ResourceLoader::loadRenderShader("resources/shaders/lighting/", "ForwardPointLight", "ForwardPointLight"));
	addShader("ForwardSpotLight", ResourceLoader::loadRenderShader("resources/shaders/lighting/", "ForwardSpotLight", "ForwardSpotLight"));

	addShader("DeferredAmbientLight", ResourceLoader::loadRenderShader("resources/shaders/lighting/", "DeferredAmbientLight", "DeferredAmbientLight"));
	addShader("DeferredDirectionalLight", ResourceLoader::loadRenderShader("resources/shaders/lighting/", "DeferredDirectionalLight", "DeferredDirectionalLight"));
	addShader("DeferredPointLight", ResourceLoader::loadRenderShader("resources/shaders/lighting/", "DeferredPointLight", "DeferredPointLight"));
	addShader("DeferredSpotLight", ResourceLoader::loadRenderShader("resources/shaders/lighting/", "DeferredSpotLight", "DeferredSpotLight"));

	addShader("GeometryShader", ResourceLoader::loadRenderShader("resources/shaders/deferred/", "GeometryShader", "GeometryShader"));
}

void Renderer::setupShader(Shader* shader, const char* type) {
	if (std::string(type) == "ForwardBasic") {
		shader->addUniform("ModelViewProjectionMatrix", "mvpMatrix");
		shader->addUniform("Texture", "tex");
		shader->addAttribute("Position", "position");
		shader->addAttribute("Colour", "colour");
		shader->addAttribute("TextureCoordinate", "textureCoord");
	} else if (std::string(type) == "DeferredBasic") {
		shader->addUniform("ModelViewProjectionMatrix", "mvpMatrix");

		shader->addUniform("WorldPositionBuffer", "buffer_worldPosition");
		shader->addUniform("ColourBuffer", "buffer_colour");
		shader->addUniform("NormalBuffer", "buffer_normal");
		shader->addUniform("ShininessBuffer", "buffer_shininess");

		shader->addAttribute("Position", "position");
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
		shader->addUniform("ModelViewProjectionMatrix", "mvpMatrix");

		shader->addUniform("AmbientLight", "ambientLight");
		shader->addUniform("SpecularIntensity", "specularIntensity");
		shader->addUniform("EyePosition", "eyePosition");

		if (std::string(type).find("Forward") != std::string::npos) {
			shader->addUniform("ModelMatrix", "mMatrix");
			shader->addUniform("NormalMatrix", "nMatrix");

			shader->addAttribute("Position", "position");
			shader->addAttribute("Normal", "normal");
			shader->addAttribute("Tangent", "tangent");
			shader->addAttribute("Bitangent", "bitangent");

			Material::addUniforms(shader);
		} else if (std::string(type).find("Deferred") != std::string::npos) {
			shader->addAttribute("Position", "position");

			shader->addUniform("WorldPositionBuffer", "buffer_worldPosition");
			shader->addUniform("ColourBuffer", "buffer_colour");
			shader->addUniform("NormalBuffer", "buffer_normal");
			shader->addUniform("ShininessBuffer", "buffer_shininess");
			shader->addUniform("DepthBuffer", "buffer_depth");

			shader->addUniform("Projection", "projection");
		}

		shader->addAttribute("TextureCoordinate", "textureCoord");

		if (std::string(type).find("DirectionalLight") != std::string::npos) {
			DirectionalLight::addUniforms(shader, "", "directionalLight.");
		} else if (std::string(type).find("PointLight") != std::string::npos) {
			PointLight::addUniforms(shader, "", "pointLight.");
		} else if (std::string(type).find("SpotLight") != std::string::npos) {
			SpotLight::addUniforms(shader, "", "spotLight.");
		}
	} else if (std::string(type) == "GeometryShader") {
		shader->addUniform("ModelMatrix", "mMatrix");
		shader->addUniform("NormalMatrix", "nMatrix");
		shader->addUniform("ModelViewProjectionMatrix", "mvpMatrix");

		Material::addUniforms(shader);

		shader->addAttribute("Position", "position");
		shader->addAttribute("TextureCoordinate", "textureCoord");
		shader->addAttribute("Normal", "normal");
		shader->addAttribute("Tangent", "tangent");
		shader->addAttribute("Bitangent", "bitangent");
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
RenderableObject2D* DeferredRenderer::m_worldPositionQuad;
RenderableObject2D* DeferredRenderer::m_normalQuad;
RenderableObject2D* DeferredRenderer::m_colourQuad;
RenderableObject2D* DeferredRenderer::m_shininessQuad;
RenderableObject2D* DeferredRenderer::m_depthQuad;

void DeferredRenderer::initialise() {
	m_geometryBuffer = new GeometryBuffer();

	int width = BaseEngine::current->getSettings()->getWindowWidth();
	int height = BaseEngine::current->getSettings()->getWindowHeight();

	m_camera = new Camera2D(Matrix4f().initOrthographic(0, width, height, 0, -1, 1));
	m_camera->update();

	Renderer::enableDeferredRendering();
	m_screenQuad = new RenderableObject2D(MeshBuilder::createQuad(width, height, new Texture(), Colour::WHITE));
	m_screenQuad->setSize(width, height);
	m_screenQuad->update();
	Renderer::disableDeferredRendering();

	m_worldPositionQuad = new RenderableObject2D(MeshBuilder::createQuad(width / 5, height / 5, new Texture(), Colour::WHITE));
	m_worldPositionQuad->getMesh()->setTexture(m_geometryBuffer->getTexture(GeometryBuffer::BUFFER_WORLD_POSITION));
	m_worldPositionQuad->setSize(width, height);
	m_worldPositionQuad->setPosition(width - (width / 5), 0);
	m_worldPositionQuad->update();

	m_colourQuad = new RenderableObject2D(MeshBuilder::createQuad(width / 5, height / 5, new Texture(), Colour::WHITE));
	m_colourQuad->getMesh()->setTexture(m_geometryBuffer->getTexture(GeometryBuffer::BUFFER_COLOUR));
	m_colourQuad->setSize(width, height);
	m_colourQuad->setPosition(width - (width / 5), (height / 5));
	m_colourQuad->update();

	m_normalQuad = new RenderableObject2D(MeshBuilder::createQuad(width / 5, height / 5, new Texture(), Colour::WHITE));
	m_normalQuad->getMesh()->setTexture(m_geometryBuffer->getTexture(GeometryBuffer::BUFFER_NORMAL));
	m_normalQuad->setSize(width, height);
	m_normalQuad->setPosition(width - (width / 5), (height / 5) * 2);
	m_normalQuad->update();

	m_shininessQuad = new RenderableObject2D(MeshBuilder::createQuad(width / 5, height / 5, new Texture(), Colour::WHITE));
	m_shininessQuad->getMesh()->setTexture(m_geometryBuffer->getTexture(GeometryBuffer::BUFFER_SHININESS));
	m_shininessQuad->setSize(width, height);
	m_shininessQuad->setPosition(width - (width / 5), (height / 5) * 3);
	m_shininessQuad->update();

	m_depthQuad = new RenderableObject2D(MeshBuilder::createQuad(width / 5, height / 5, new Texture(), Colour::WHITE));
	m_depthQuad->getMesh()->setTexture(m_geometryBuffer->getTexture(GeometryBuffer::BUFFER_DEPTH));
	m_depthQuad->setSize(width, height);
	m_depthQuad->setPosition(width - (width / 5), (height / 5) * 4);
	m_depthQuad->update();
}

void DeferredRenderer::renderToScreen(bool bindBuffers, bool unbindBuffers) {
	if (m_screenQuad != NULL) {
		Renderer::addCamera(m_camera);

		Shader* currentShader = Renderer::getShader(m_screenQuad->getMesh()->getShaderType());
		if (currentShader != NULL) {
			Matrix4f mvp = (Renderer::getCamera()->getProjectionViewMatrix() * m_screenQuad->getModelMatrix()).transpose();
			currentShader->use();

			GLuint b1 = 0;
			GLuint b2 = 0;
			GLuint b3 = 0;
			GLuint b4 = 0;
			GLuint b5 = 0;

			if (bindBuffers) {
				b1 = Renderer::bindTexture(m_geometryBuffer->getTexture(GeometryBuffer::BUFFER_WORLD_POSITION));
				b2 = Renderer::bindTexture(m_geometryBuffer->getTexture(GeometryBuffer::BUFFER_COLOUR));
				b3 = Renderer::bindTexture(m_geometryBuffer->getTexture(GeometryBuffer::BUFFER_NORMAL));
				b4 = Renderer::bindTexture(m_geometryBuffer->getTexture(GeometryBuffer::BUFFER_SHININESS));
				b5 = Renderer::bindTexture(m_geometryBuffer->getTexture(GeometryBuffer::BUFFER_DEPTH));
			} else {
				b5 = Renderer::getNumBoundTextures() - 1;
				b4 = b5 - 1;
				b3 = b4 - 1;
				b2 = b3 - 1;
				b1 = b2 - 1;
			}

			glUniform1i(currentShader->getUniformLocation("WorldPositionBuffer"), b1);
			glUniform1i(currentShader->getUniformLocation("ColourBuffer"), b2);
			glUniform1i(currentShader->getUniformLocation("NormalBuffer"), b3);
			glUniform1i(currentShader->getUniformLocation("ShininessBuffer"), b4);
			glUniform1i(currentShader->getUniformLocation("DepthBuffer"), b5);

			glUniformMatrix4fv(currentShader->getUniformLocation("Projection"), 1, GL_FALSE, &(Renderer::getCamera()->getProjectionMatrix().m_values[0][0]));

			glUniformMatrix4fv(currentShader->getUniformLocation("ModelViewProjectionMatrix"), 1, GL_FALSE, &(mvp.m_values[0][0]));
			m_screenQuad->getMesh()->render();
			currentShader->stopUsing();

			if (unbindBuffers)
				Renderer::unbindTetxures();
		}

		Renderer::removeCamera();
	}
}

void DeferredRenderer::renderBuffers() {
	Renderer::addCamera(m_camera);
	m_worldPositionQuad->render();
	m_colourQuad->render();
	m_normalQuad->render();
	m_shininessQuad->render();
	m_depthQuad->render();
	Renderer::removeCamera();
}

/***************************************************************************************************/
