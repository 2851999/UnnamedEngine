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

#include "GeometryBuffer.h"

#include "../Game.h"

/***************************************************************************************************
 * The GeometryBuffer class
 ***************************************************************************************************/

GeometryBuffer::GeometryBuffer() {
	m_fbo = new FBO(GL_FRAMEBUFFER);
	TextureParameters parameters = TextureParameters().setFilter(GL_NEAREST).setShouldClamp(true);
	int width = Game::current->getSettings()->getWindowWidth();
	int height = Game::current->getSettings()->getWindowHeight();
	m_fbo->add(new RenderTexture(width, height, GL_RGBA16F, GL_RGBA, GL_COLOR_ATTACHMENT0, GL_FLOAT, parameters));
	m_fbo->add(new RenderTexture(width, height, GL_RGBA16F, GL_RGBA, GL_COLOR_ATTACHMENT1, GL_FLOAT, parameters));
	m_fbo->add(new RenderTexture(width, height, GL_RGBA16F, GL_RGBA, GL_COLOR_ATTACHMENT2, GL_FLOAT, parameters));
	m_fbo->add(new RenderTexture(width, height, GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_DEPTH_ATTACHMENT, GL_FLOAT, parameters));
	m_fbo->setup();
}

/***************************************************************************************************/
