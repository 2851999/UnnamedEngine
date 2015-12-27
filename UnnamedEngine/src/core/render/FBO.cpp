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
	m_attachments = NULL;
	m_numAttachments = 0;
}

void FBO::setup() {
	glBindFramebuffer(m_target, m_pointer);

	//Check the textures and make sure any depth attachments are discounted
	for (unsigned int a = 0; a < m_textures.size(); a++) {
		if (m_textures.at(a)->getAttachment() != GL_DEPTH_ATTACHMENT)
			m_numAttachments++;
	}

	//Setup the array of attachments
	m_attachments = new GLuint[m_numAttachments];

	//The current attachment
	unsigned int currentAttachment = 0;

	for (unsigned int a = 0; a < m_textures.size(); a++) {
		glFramebufferTexture2D(m_target, m_textures.at(a)->getAttachment(), m_textures.at(a)->getParameters().getTarget(), m_textures.at(a)->getTexture(), 0);

		//Assign the next attachment
		if (m_textures.at(a)->getAttachment() != GL_DEPTH_ATTACHMENT) {
			m_attachments[currentAttachment] = m_textures.at(a)->getAttachment();
			currentAttachment++;
		}
	}

	GLuint status = glCheckFramebufferStatus(m_target);
	if (status != GL_FRAMEBUFFER_COMPLETE)
		logError("Can't initialise the FBO");
	unbind();
}

void FBO::bind() {
	glBindFramebuffer(m_target, m_pointer);

	glDrawBuffers(m_numAttachments, m_attachments);
}

void FBO::unbind() {
	glBindFramebuffer(m_target, 0);
}

/***************************************************************************************************/
