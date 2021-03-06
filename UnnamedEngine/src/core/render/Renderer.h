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

#ifndef CORE_RENDERER_H_
#define CORE_RENDERER_H_

#include "../Mesh.h"
#include "../Camera.h"
#include "Shader.h"
#include "Material.h"

/***************************************************************************************************
 * The Renderer class is responsible for rendering
 ***************************************************************************************************/

class Renderer {
private:
	static std::vector<Camera*> m_cameras;
	static std::map<std::string, RenderShader*> m_shaders;

	static std::vector<Texture*> m_boundTextures;

	static Shader* m_overrideShader;
public:
	static Texture* TEXTURE_BLANK;
	virtual ~Renderer() {}
	static inline void addCamera(Camera* camera) { m_cameras.push_back(camera); }
	static inline void addShader(std::string type, RenderShader* shader) { m_shaders.insert(std::pair<std::string, RenderShader*>(type, shader)); }
	static inline void removeCamera() { m_cameras.pop_back(); }
	static inline void removeShader() { m_shaders.erase(m_shaders.end()); }
	static inline void setShader(Shader* overrideShader) { m_overrideShader = overrideShader; }
	static inline void resetShader() { m_overrideShader = NULL; }
	static inline Camera* getCamera() { return m_cameras.back(); }
	static inline RenderShader* getRenderShader(std::string type) { return m_shaders.at(type); }
	static inline Shader* getShader(std::string type) {
		if (m_overrideShader == NULL)
			return m_shaders.at(type)->getShader();
		else
			return m_overrideShader;
	}
	static void initialise();
	static void setupShader(Shader* shader, const char* type);
	static void render(Mesh* mesh, Matrix4f modelMatrix, std::string shaderType);
	static inline void render(Mesh* mesh, Matrix4f modelMatrix) { render(mesh, modelMatrix, mesh->getRenderData()->getShaderType()); }
	static GLuint bindTexture(Texture* texture);
	static void unbindTetxures();
};

/***************************************************************************************************/

#endif /* CORE_RENDERER_H_ */
