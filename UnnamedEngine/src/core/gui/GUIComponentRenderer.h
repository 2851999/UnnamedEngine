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

#ifndef CORE_GUI_GUICOMPONENTRENDERER_H_
#define CORE_GUI_GUICOMPONENTRENDERER_H_

#include <vector>
#include "Font.h"
#include "../Vector.h"
#include "../Texture.h"
#include "../Mesh.h"

/***************************************************************************************************
 * The GUIComponentRenderer class will handle the rendering of a GUIComponent
 ***************************************************************************************************/

class GUIComponentRenderer {
public:
	static Font* defaultFont;
	std::vector<Colour> colours;
	std::vector<Texture*> textures;
	Colour inactiveColour;
	Texture* inactiveTexture;
	int componentIndex;
	RenderableObject2D* entity;
	Font* font;
	GUIComponentRenderer(RenderableObject2D* entity);
	GUIComponentRenderer(Mesh* mesh) : GUIComponentRenderer(new RenderableObject2D(mesh)) {}
	void render(Object2D* object, bool active);
	inline void set(std::vector<Colour> colours) { this->colours = colours; }
	inline void set(std::vector<Texture*> textures) { this->textures = textures; }
	inline void setComponentIndex(int componentIndex) { this->componentIndex = componentIndex; }
	inline void setFont(Font* font) { this->font = font; }
	inline std::vector<Colour> getColours() { return colours; }
	inline std::vector<Texture*> getTextures() { return textures; }
	inline bool shouldUseColours() { return colours.size() > 0; }
	inline bool shouldUseTextures() { return textures.size() > 0; }
	inline bool shouldUseInactiveColour() { return inactiveColour.getR() != -1; }
	inline bool shouldUseInactiveTexture() { return inactiveTexture != NULL; }

	int getTotalComponents();
};

/***************************************************************************************************/

#endif /* CORE_GUI_GUICOMPONENTRENDERER_H_ */
