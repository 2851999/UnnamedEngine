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

#include "Texture.h"
#include "Game.h"
#define STB_IMAGE_IMPLEMENTATION
#include <GL\stb_image.h>

/***************************************************************************************************
 * The TextureParameters class
 ***************************************************************************************************/

GLuint TextureParameters::DEFAULT_TARGET = GL_TEXTURE_2D;
GLuint TextureParameters::DEFAULT_FILTER = GL_NEAREST;
GLuint TextureParameters::DEFAULT_CLAMP = GL_CLAMP_TO_EDGE;
bool TextureParameters::DEFAULT_SHOULD_CLAMP = false;

void TextureParameters::apply(GLuint texture, bool bind, bool unbind) {
	if (bind)
		glBindTexture(m_target, texture);
	glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, m_filter);
	glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, m_filter);
	if (m_shouldClamp) {
		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, m_clamp);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, m_clamp);
		if (m_target == GL_TEXTURE_CUBE_MAP)
			glTexParameteri(m_target, GL_TEXTURE_WRAP_R, m_clamp);
	}
	if (m_filter == GL_NEAREST_MIPMAP_NEAREST ||
		m_filter == GL_NEAREST_MIPMAP_LINEAR ||
		m_filter == GL_LINEAR_MIPMAP_NEAREST ||
		m_filter == GL_LINEAR_MIPMAP_LINEAR) {
		glGenerateMipmap(m_target);
		glTexParameterf(m_target, GL_TEXTURE_MAX_ANISOTROPY_EXT, Game::current->getSettings()->getVideoMaxAnisotropicSamples());
	}
	if (unbind)
		glBindTexture(m_target, 0);
}

/***************************************************************************************************/

/***************************************************************************************************
 * The Texture class
 ***************************************************************************************************/

Texture* Texture::loadTexture(const char* path, TextureParameters parameters, bool applyParameters) {
	int w, h, numC;
	unsigned char* image = stbi_load(path, &w, &h, &numC, 0);
	if (image == nullptr) {
		logError("Failed to load the image from the path '" + to_string(path) + "'");
		return NULL;
	}
	GLuint colourMode = 0;
	if (numC == 1)
		colourMode = GL_RED;
	else if (numC == 2)
		colourMode = GL_RG;
	else if (numC == 3)
		colourMode = GL_RGB;
	else if (numC == 4)
		colourMode = GL_RGBA;
	Texture* texture = new Texture(parameters);
	texture->setWidth(w);
	texture->setHeight(h);
	texture->setNumComponents(numC);

	texture->bind();

	glTexImage2D(parameters.getTarget(), 0, colourMode, w, h, 0, colourMode, GL_UNSIGNED_BYTE, image);

	if (applyParameters)
		texture->applyParameters(false, true);

	stbi_image_free(image);
	return texture;
}

/***************************************************************************************************/
