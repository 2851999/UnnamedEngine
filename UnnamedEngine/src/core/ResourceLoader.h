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

#ifndef CORE_RESOURCELOADER_H_
#define CORE_RESOURCELOADER_H_

#include "../utils/FileUtils.h"
#include "render/Shader.h"
#include "gui/Font.h"
#include "Texture.h"

/***************************************************************************************************
 * The ResourceLoader class creates methods that can be used to load resources
 ***************************************************************************************************/

class ResourceLoader {
public:
	static inline Texture* loadTexture(const char* path) { return Texture::loadTexture(path); }
	static inline Texture* loadTexture(const char* path, TextureParameters parameters) { return Texture::loadTexture(path, parameters, true); }
	static inline Texture* loadTexture(const char* path, TextureParameters parameters, bool applyParameters) { return Texture::loadTexture(path, parameters, applyParameters); }
	static inline GLuint   loadShader (const char* path, const char* name, GLenum type) { return Shader::loadShaderFromPath(path, name, type); }
	static        Shader*  loadShader (const char* path, const char* vertexShaderName, const char* fragmentShaderName);
	static        Shader*  loadShader (const char* path, const char* name);
	static        RenderShader* loadRenderShader(const char* path, const char* name, const char* type);
	static        Font*    loadFont   (const char* path, float gridSize, float size);
	static        Font*    loadFont   (const char* path, float gridSize, float size, Colour colour);
};

/***************************************************************************************************/

#endif /* CORE_RESOURCELOADER_H_ */
