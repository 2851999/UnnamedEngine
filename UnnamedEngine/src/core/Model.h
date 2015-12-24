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

#ifndef CORE_MODEL_H_
#define CORE_MODEL_H_

#include <vector>

#include "Object.h"
#include "Mesh.h"

/***************************************************************************************************
 * The Model class is used to store a model that can be rendered
 ***************************************************************************************************/

class Model : public RenderableObject3D {
private:
	std::vector<Mesh*> m_meshes;
public:
	Model() { }
	virtual ~Model() {}
	inline void addMesh(Mesh* mesh) { m_meshes.push_back(mesh); }
	void render();

	inline Mesh* getMesh(unsigned int n) { return m_meshes[n]; }

	static Model* loadModel(const char* path, const char* fileName, std::string shaderType);
	static inline Model* loadModel(const char* path, const char* fileName) { return loadModel(path, fileName, "Material"); }

	inline void setShaderType(std::string shaderType) {
		for (unsigned int a = 0; a < m_meshes.size(); a++)
			m_meshes.at(a)->setShaderType(shaderType);
	}
	inline std::string getShaderType() { return m_meshes.at(0)->getShaderType(); }
};

/***************************************************************************************************/

#endif /* CORE_MODEL_H_ */
