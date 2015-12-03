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

#include "Scene.h"
#include "Renderer.h"

/***************************************************************************************************
 * The Scene class
 ***************************************************************************************************/

void Scene::update() {
	for (unsigned int a = 0; a < m_objects.size(); a++)
		m_objects.at(a)->update();
}

void Scene::render(Vector3f cameraPosition) {
	if (m_lightingEnabled) {
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

				Shader* shader = Renderer::getShader("");

				for (unsigned int b = 0; b < m_objects.size(); b++) {

					Matrix4f normalMatrix = m_objects.at(b)->getModelMatrix().inverse().transpose();

					shader->setUniform("NormalMatrix", normalMatrix);
					shader->setUniform("SpecularIntensity", m_specularIntensity);
					shader->setUniform("EyePosition", cameraPosition);

					m_objects.at(b)->render();

				}

				Renderer::resetShader();
			}

			glDepthFunc(GL_LESS);
			glDepthMask(true);
			glDisable(GL_BLEND);

		}
	}
}

/***************************************************************************************************/
