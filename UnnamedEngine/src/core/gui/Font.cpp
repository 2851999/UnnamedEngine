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

#include "Font.h"

/***************************************************************************************************
 * The BitmapText class
 ***************************************************************************************************/

void BitmapText::update(std::string text) {
	RenderableObject2D::update();
	if (text != m_currentText) {
		m_currentText = text;

		getMesh()->getData()->clearPositions();
		getMesh()->getData()->clearColours();
		getMesh()->getData()->clearTextureCoords();
		getMesh()->getData()->clearIndices();

		float x = 0;

		float mapWidth = getMesh()->getTexture()->getWidth();
		float mapHeight = getMesh()->getTexture()->getHeight();

		for (unsigned int a = 0; a < text.length(); a++) {
			int asciiCode = (int) text.c_str()[a];

			float cellX = (((int) asciiCode % m_gridWidth) * m_cellWidth);
			float cellY = (float) ((floor((int) asciiCode / m_gridHeight)) * m_cellHeight);

			getMesh()->getData()->addPosition(Vector3f(x, 0.0f, 0.0f));
			getMesh()->getData()->addPosition(Vector3f(x + (m_cellWidth / m_cellHeight) * m_fontSize, 0.0f, 0.0f));
			getMesh()->getData()->addPosition(Vector3f(x + (m_cellWidth / m_cellHeight) * m_fontSize, m_fontSize, 0.0f));
			getMesh()->getData()->addPosition(Vector3f(x, m_fontSize, 0.0f));

			getMesh()->getData()->addColour(m_colour);
			getMesh()->getData()->addColour(m_colour);
			getMesh()->getData()->addColour(m_colour);
			getMesh()->getData()->addColour(m_colour);

			getMesh()->getData()->addTextureCoord(Vector2f(cellX / mapWidth, cellY / mapHeight));
			getMesh()->getData()->addTextureCoord(Vector2f((cellX + m_cellWidth) / mapWidth, cellY / mapHeight));
			getMesh()->getData()->addTextureCoord(Vector2f((cellX + m_cellWidth) / mapWidth, (cellY + m_cellHeight) / mapHeight));
			getMesh()->getData()->addTextureCoord(Vector2f(cellX / mapWidth, (cellY + m_cellHeight) / mapHeight));

			getMesh()->getData()->addIndex((a * 4) + 0);
			getMesh()->getData()->addIndex((a * 4) + 1);
			getMesh()->getData()->addIndex((a * 4) + 2);
			getMesh()->getData()->addIndex((a * 4) + 2);
			getMesh()->getData()->addIndex((a * 4) + 3);
			getMesh()->getData()->addIndex((a * 4) + 0);

			x += ((m_cellWidth / m_cellHeight) * m_fontSize) / 1.5f;
		}
		getMesh()->updateVertices();
		getMesh()->updateColours();
		getMesh()->updateTextureCoords();
		getMesh()->updateIndices();
	}
}

/***************************************************************************************************/

/***************************************************************************************************
 * The Font class
 ***************************************************************************************************/

void Font::render(std::string text, float x, float y) {
	m_bitmapFont->setPosition(Vector2f(x, y));
	m_bitmapFont->update(text);
	m_bitmapFont->render();
}

void Font::renderAtCentre(std::string text, Object2D* object, Vector2f offset) {
	Vector2f centre = object->getCentre();
	render(text, centre.getX() - (getWidth(text) / 2) + offset.getX(), centre.getY() - (getHeight(text) / 2) + offset.getY());
}

Font* Font::loadFont(const char* path, float gridSize, float size, Colour colour) {
	return new Font(new BitmapText(Texture::loadTexture(path, TextureParameters().setFilter(GL_NEAREST), true), gridSize, size, colour));
}

/***************************************************************************************************/
