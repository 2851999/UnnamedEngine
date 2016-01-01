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

#ifndef CORE_GUI_FONT_H_
#define CORE_GUI_FONT_H_

#include "../Vector.h"
#include "../Mesh.h"
#include "../Object.h"

/***************************************************************************************************
 * The BitmapText class
 ***************************************************************************************************/

class BitmapText : public RenderableObject2D {
private:
	float m_fontSize;
	int m_gridWidth;
	int m_gridHeight;
	float m_cellWidth;
	float m_cellHeight;
	std::string m_currentText;
	Colour m_colour;

public:
	BitmapText(Texture* texture, int gridSize, float fontSize, Colour colour) :
		RenderableObject2D(MeshBuilder::createQuad(1, 1, texture, Colour::WHITE)) {
		m_fontSize = fontSize;
		m_gridWidth = gridSize;
		m_gridHeight = gridSize;
		m_cellWidth = (float) texture->getWidth() / (float) m_gridWidth;
		m_cellHeight = (float) texture->getHeight() / (float) m_gridHeight;
		m_fontSize = fontSize;
		m_colour = colour;
		getMesh()->setTexture(texture);
	}

	void update() { RenderableObject2D::update(); }
	void update(std::string text);

	inline float getWidth(std::string text) {
		return (text.length() * (((m_cellWidth / m_cellHeight) * m_fontSize) / 1.5f));
	}
	inline float getHeight(std::string text) {
		return m_fontSize;
	}

	inline void setFontSize(float fontSize) { m_fontSize = fontSize; }
	inline float getFontSize() { return m_fontSize; }
};

/***************************************************************************************************/

/***************************************************************************************************
 * The Font class
 ***************************************************************************************************/

class Font {
private:
	BitmapText* m_bitmapFont;
public:
	Font(BitmapText* bitmapFont) { m_bitmapFont = bitmapFont; }
	void render(std::string, float x, float y);
	void renderAtCentre(std::string text, Object2D* object, Vector2f offset);
	inline void renderAtCentre(std::string text, Object2D* object) { renderAtCentre(text, object, Vector2f(0, 0)); }
	inline void setSize(float size) { m_bitmapFont->setFontSize(size); }
	inline float getWidth(std::string text) { return m_bitmapFont->getWidth(text); }
	inline float getHeight(std::string text) { return m_bitmapFont->getHeight(text); }

	static Font* loadFont(const char* path, float gridSize, float size, Colour colour);
	static inline Font* loadFont(const char* path, float gridSize, float size) { return loadFont(path, gridSize, size, Colour::WHITE); }
};

/***************************************************************************************************/

#endif /* CORE_GUI_FONT_H_ */
