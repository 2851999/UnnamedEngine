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

#include<GL/GLEW/glew.h>

#include "FBO.h"

/***************************************************************************************************
 * The FBO class
 ***************************************************************************************************/

FBO::FBO(GLuint target) : m_target(target) {
	glGenFramebuffers(1, &m_pointer);
}

void FBO::setup() {
	glBindFramebuffer(m_target, m_pointer);

	for (unsigned int a = 0; a < m_textures.size(); a++) {
		glFramebufferTexture2D(m_target, m_textures.at(a)->getAttachment(), m_textures.at(a)->getParameters().getTarget(), m_textures.at(a)->getTexture(), 0);
	}

	GLuint status = glCheckFramebufferStatus(m_target);
	if (status != GL_FRAMEBUFFER_COMPLETE)
		logError("Can't initialise the FBO");
	unbind();
}

void FBO::bind() {
	glBindFramebuffer(m_target, m_pointer);
	/* Should do this in setup */
	GLenum buffers[m_textures.size()];
	for (unsigned int a = 0; a < m_textures.size(); a++) {
		if (m_textures.at(a)->getAttachment() != GL_DEPTH_ATTACHMENT)
			buffers[a] = m_textures.at(a)->getAttachment();
	}

	for (unsigned int a = 0; a < m_textures.size(); a++)
		std::cout << buffers[a] << std::endl;
	glDrawBuffers(m_textures.size() - 1, buffers); //Should not stay like this, but GL_DEPTH_ATTACHMENT should not be bound, nor the last value here
}

void FBO::unbind() {
	glBindFramebuffer(m_target, 0);
}

/***************************************************************************************************/
