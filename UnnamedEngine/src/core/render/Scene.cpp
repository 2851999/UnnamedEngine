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

#include "Scene.h"
#include "Renderer.h"
#include "../Game.h"

/***************************************************************************************************
 * The Scene class
 ***************************************************************************************************/

void Scene::update() {
	for (unsigned int a = 0; a < m_objects.size(); a++)
		m_objects.at(a)->update();
}

void Scene::render(Vector3f cameraPosition) {
	//Check how the rendering should be done
	if (m_lightingEnabled && ! Game::current->getSettings()->getVideoDeferredRendering()) {
		//Forward lighting

		Renderer::setShader(Renderer::getShader("AmbientLight"));
		Shader* shader = Renderer::getShader("");
		shader->use();
		shader->setUniform("AmbientLight", m_ambientLight);

		for (unsigned int a = 0; a < m_objects.size(); a++)
			m_objects.at(a)->render();

		Renderer::resetShader();

		if (m_lights.size() > 0) {

			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			glDepthMask(false);
			glDepthFunc(GL_EQUAL);

			for (unsigned int a = 0; a < m_lights.size(); a++) {
				m_lights.at(a)->apply();

				shader = Renderer::getShader("");
				shader->use();

				for (unsigned int b = 0; b < m_objects.size(); b++) {

					Matrix4f modelMatrix = m_objects.at(b)->getModelMatrix();

					shader->setUniform("ModelMatrix", m_objects.at(b)->getModelMatrix());
					shader->setUniform("NormalMatrix", modelMatrix.to3x3().inverse().transpose());

					shader->setUniform("SpecularIntensity", m_specularIntensity);
					shader->setUniform("EyePosition", cameraPosition);

					m_objects.at(b)->render(); //Stops using the shader

				}

				Renderer::resetShader();
			}

			glDepthFunc(GL_LESS);
			glDepthMask(true);
			glDisable(GL_BLEND);

		}
	} else if (Game::current->getSettings()->getVideoDeferredRendering()) {
		//Deferred geometry

		Renderer::setShader(Renderer::getShader("GeometryShader"));
		DeferredRenderer::start();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D);

		Renderer::enableDeferredRendering();
		Shader* shader = Renderer::getShader("");
		shader->use();

		for (unsigned int a = 0; a < m_objects.size(); a++) {
			Matrix4f modelMatrix = m_objects.at(a)->getModelMatrix();

			shader->setUniform("ModelMatrix", m_objects.at(a)->getModelMatrix());
			shader->setUniform("NormalMatrix", modelMatrix.to3x3().inverse().transpose());

			m_objects.at(a)->render();
		}

		Renderer::resetShader();
		Renderer::disableDeferredRendering();

		DeferredRenderer::stop();
		Renderer::resetShader();
	} else {
		for (unsigned int a = 0; a < m_objects.size(); a++)
			m_objects.at(a)->render();
	}
}

void Scene::renderFinal(Vector3f cameraPosition) {
	//Check how the rendering should be done
	if (m_lightingEnabled && Game::current->getSettings()->getVideoDeferredRendering()) {
		//Deferred lighting

		Renderer::enableDeferredRendering();
		Renderer::setShader(Renderer::getShader("AmbientLight"));
		Shader* shader = Renderer::getShader("");
		shader->use();
		shader->setUniform("AmbientLight", m_ambientLight);
		DeferredRenderer::renderToScreen(true, false);

		Renderer::resetShader();

		if (m_lights.size() > 0) {

			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			glDepthMask(false);
			glDepthFunc(GL_EQUAL);

			for (unsigned int a = 0; a < m_lights.size(); a++) {
				m_lights.at(a)->apply();

				shader = Renderer::getShader("");
				shader->use();

				shader->setUniform("SpecularIntensity", m_specularIntensity);
				shader->setUniform("EyePosition", cameraPosition);

				DeferredRenderer::renderToScreen(false, false);

				Renderer::resetShader();
			}

			glDepthFunc(GL_LESS);
			glDepthMask(true);
			glDisable(GL_BLEND);

		}
		Renderer::unbindTetxures();
		Renderer::disableDeferredRendering();
	} else if (Game::current->getSettings()->getVideoDeferredRendering()) {
		//Deferred

		Renderer::enableDeferredRendering();
		DeferredRenderer::renderToScreen();
		Renderer::disableDeferredRendering();
	}
}

/***************************************************************************************************/
