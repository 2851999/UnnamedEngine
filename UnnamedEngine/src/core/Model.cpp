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

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include <assimp/vector3.h>

#include "../utils/StringUtils.h"
#include "../utils/Logging.h"
#include "render/Renderer.h"
#include "Model.h"

/***************************************************************************************************
 * The Model class
 ***************************************************************************************************/

void Model::render() {
	for (unsigned int a = 0; a < m_meshes.size(); a++)
		Renderer::render(m_meshes[a], getModelMatrix());
}

Model* Model::loadModel(const char* path, const char* fileName, std::string shaderType) {
	const struct aiScene* scene = aiImportFile((to_string(path) + to_string(fileName)).c_str(), aiProcess_Triangulate | aiProcess_FlipUVs); //aiProcessPreset_TargetRealtime_MaxQuality
	if (scene != NULL) {
		Model* model = new Model();
		unsigned int numMeshes = scene->mNumMeshes;

		for (unsigned int a = 0; a < numMeshes; a++) {
			MeshData* currentData = new MeshData(false, false, false, false);
			const struct aiMesh* currentMesh = scene->mMeshes[a];
			for (unsigned int b = 0; b < currentMesh->mNumFaces; b++) {
				struct aiFace currentFace = currentMesh->mFaces[b];
				for (int c = 0; c < 3; c++) { //Assumes model is triangulated
					aiVector3D position = currentMesh->mVertices[currentFace.mIndices[c]];
					currentData->addPosition(Vector3f(position.x, position.y, position.z));
					//currentData->addColour(Colour::WHITE); //Make sure the mesh actually has a base colour
					if (currentMesh->mTextureCoords[0] != NULL) {
						aiVector3D textureCoord = currentMesh->mTextureCoords[0][currentFace.mIndices[c]];
						currentData->addTextureCoord(Vector2f(textureCoord.x, textureCoord.y));
					}
					if (currentMesh->mNormals != NULL) {
						aiVector3D normal = currentMesh->mNormals[currentFace.mIndices[c]];
						currentData->addNormal(Vector3f(normal.x, normal.y, normal.z));
					}
				}
			}
			Mesh* mesh = new Mesh(currentData, shaderType);
			if (scene->mMaterials[0] != NULL) {
				aiMaterial* currentMaterial = scene->mMaterials[currentMesh->mMaterialIndex];
				Material* material = new Material();
				if (currentMaterial->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
					aiString p;
					currentMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &p, NULL, NULL, NULL, NULL, NULL);
					material->setDiffuseTexture(Texture::loadTexture((to_string(path) + to_string(p.C_Str())).c_str()));
				}
				aiColor3D ambientColour = aiColor3D(1.0f, 1.0f, 1.0f);
				currentMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambientColour);
				material->setAmbientColour(Colour(ambientColour.r, ambientColour.g, ambientColour.b, 1.0f));

				aiColor3D diffuseColour = aiColor3D(1.0f, 1.0f, 1.0f);
				currentMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColour);
				material->setDiffuseColour(Colour(diffuseColour.r, diffuseColour.g, diffuseColour.b, 1.0f));

				aiColor3D specularColour = aiColor3D(1.0f, 1.0f, 1.0f);
				currentMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specularColour);
				material->setSpecularColour(Colour(specularColour.r, specularColour.g, specularColour.b, 1.0f));

				float shininess = 0.0f;
				currentMaterial->Get(AI_MATKEY_SHININESS, shininess);
				material->setShininess(shininess);

				mesh->getRenderData()->setMaterial(material);
			}
			model->addMesh(mesh);
		}
		aiReleaseImport(scene);
		return model;
	} else {
		logDebug("The model '" + to_string(path) + to_string(fileName) + "' could not be loaded");
		return NULL;
	}
}

/***************************************************************************************************/
