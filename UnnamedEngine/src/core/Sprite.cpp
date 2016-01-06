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

#include "Sprite.h"

/***************************************************************************************************
 * The TextureEntity2D class
 ***************************************************************************************************/

void TextureEntity2D::setTexture(Texture* texture) {
	m_mesh->setTexture(texture);
	m_mesh->getData()->clearTextureCoords();
	MeshBuilder::addQuadT(m_mesh->getData(), texture);
	m_mesh->updateTextureCoords();
}

/***************************************************************************************************/

/***************************************************************************************************
 * The Animation2D class
 ***************************************************************************************************/

void Animation2D::update() {
	//Make sure this animation is running
	if (m_running) {
		//Check the timer
		if (m_timer->hasTimePassed(m_timeBetweenFrame)) {
			//Increment the current frame
			m_currentFrame++;
			//Check the current frame
			if (hasFinished()) {
				//Check to see whether this animation should repeat
				if (m_repeat) {
					//Reset this animation
					reset();
					//Start this animation
					start();
				} else
					//Stop this animation
					stop();
			} else {
				updateAnimation();
				//Restart the timer
				m_timer->restart();
			}
		}
	}
}

void Animation2D::start() {
	//Set running to true
	m_running = true;
	//Start the timer
	m_timer->start();
	startAnimation();
	updateAnimation();
}

void Animation2D::stop() {
	//Set running to false
	m_running = false;
	//Stop the timer
	m_timer->stop();
	stopAnimation();
}

void Animation2D::reset() {
	//Reset the variables
	m_running = false;
	m_currentFrame = 0;
	m_timer->reset();
	resetAnimation();
}

void Animation2D::restart() {
	stop();
	reset();
	start();
}

/***************************************************************************************************/

/***************************************************************************************************
 * The TextureAnimation2D class
 ***************************************************************************************************/

void TextureAnimation2D::updateAnimation() {
	if (m_textures.size() > 0)
		getEntity()->getMesh()->setTexture(m_textures.at(getCurrentFrame()));
	else {
		if (m_currentTile != getCurrentFrame()) {
			if (m_tileSet != NULL)
				getEntity()->getMesh()->setTexture(m_tileSet);
			m_currentTile = getCurrentFrame();
			//Get the coordinates of the tile in pixels
			float x = (m_currentTile % m_tilesPerRow) * m_tileWidth;
			float y = (m_currentTile / m_tilesPerRow) * m_tileHeight;
			//The texture coordinates
			float top = y / m_tileSetHeight;
			float left = x / m_tileSetWidth;
			float bottom = top + (m_tileHeight / m_tileSetHeight);
			float right = left + (m_tileWidth / m_tileSetWidth);

			getEntity()->getMesh()->getData()->clearTextureCoords();
			getEntity()->getMesh()->getData()->addTextureCoord(Vector2f(left, top));
			getEntity()->getMesh()->getData()->addTextureCoord(Vector2f(left, bottom));
			getEntity()->getMesh()->getData()->addTextureCoord(Vector2f(right, bottom));
			getEntity()->getMesh()->getData()->addTextureCoord(Vector2f(right, top));
			getEntity()->getMesh()->updateTextureCoords();
		}
	}
}

void TextureAnimation2D::resetAnimation() {
	if (m_textures.size() > 0)
		getEntity()->getMesh()->setTexture(m_textures.at(getCurrentFrame()));
	else
		m_currentTile = -1;
}

bool TextureAnimation2D::hasFinished() {
	if (m_textures.size() > 0)
		return getCurrentFrame() == (int) m_textures.size();
	else
		return getCurrentFrame() == m_numberOfTiles;
}

/***************************************************************************************************/

/***************************************************************************************************
 * The Sprite2D class
 ***************************************************************************************************/

void Sprite2D::update() {
	TextureEntity2D::update();
	if (m_currentAnimation != NULL)
		m_currentAnimation->update();
}

void Sprite2D::start(std::string name) {
	m_currentAnimation = m_animations.at(name);
	m_currentAnimation->start();
}

/***************************************************************************************************/
