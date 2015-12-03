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

#include "SkyBox.h"
#include "render/Renderer.h"

/***************************************************************************************************
 * The SkyBox class
 ***************************************************************************************************/

SkyBox::SkyBox(std::string path, std::string front, std::string back, std::string left, std::string right, std::string top, std::string bottom, float size) {
	m_box = RenderableObject3D(MeshBuilder::createCube(size, size, size, "SkyBox"));
	Texture* texture = new Texture(TextureParameters().setTarget(GL_TEXTURE_CUBE_MAP));
	texture->bind();
	Texture::loadTexture((path + back).c_str(), TextureParameters().setTarget(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z), false);
	Texture::loadTexture((path + front).c_str(), TextureParameters().setTarget(GL_TEXTURE_CUBE_MAP_POSITIVE_Z), false);
	Texture::loadTexture((path + left).c_str(), TextureParameters().setTarget(GL_TEXTURE_CUBE_MAP_NEGATIVE_X), false);
	Texture::loadTexture((path + right).c_str(), TextureParameters().setTarget(GL_TEXTURE_CUBE_MAP_POSITIVE_X), false);
	Texture::loadTexture((path + bottom).c_str(), TextureParameters().setTarget(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y), false);
	Texture::loadTexture((path + top).c_str(), TextureParameters().setTarget(GL_TEXTURE_CUBE_MAP_POSITIVE_Y), false);
	texture->applyParameters(false, true);
	m_box.getMesh()->setTexture(texture);
}

void SkyBox::update(Vector3f cameraPosition) {
	m_box.setPosition(cameraPosition * -1);
}

void SkyBox::render() {
	m_box.update();
	glDepthMask(false);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	Renderer::render(m_box.getMesh(), m_box.getModelMatrix(), "SkyBox");
	glDepthMask(true);
}

/***************************************************************************************************/
