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

#include "render/Renderer.h"
#include "ResourceLoader.h"

/***************************************************************************************************
 * The ResourceLoader class
 ***************************************************************************************************/

Shader* ResourceLoader::loadShader(const char* path, const char* vertexShaderName, const char* fragmentShaderName) {
	return new Shader(loadShader(path, vertexShaderName, GL_VERTEX_SHADER),
					  loadShader(path, fragmentShaderName, GL_FRAGMENT_SHADER));
}

Shader* ResourceLoader::loadShader(const char* path, const char* name) {
	std::string p = std::string(name);
	return new Shader(loadShader(path, (p + ".vs").c_str(), GL_VERTEX_SHADER),
					  loadShader(path, (p + ".fs").c_str(), GL_FRAGMENT_SHADER));
}

RenderShader* ResourceLoader::loadRenderShader(const char* path, const char* name, const char* type) {
	Shader* shader = loadShader(path, name);
	Renderer::setupShader(shader, type);
	return new RenderShader(shader);
}

Font* ResourceLoader::loadFont(const char* path, float gridSize, float size) {
	return Font::loadFont(path, gridSize, size);
}

Font* ResourceLoader::loadFont(const char* path, float gridSize, float size, Colour colour) {
	return Font::loadFont(path, gridSize, size, colour);
}

/***************************************************************************************************/
