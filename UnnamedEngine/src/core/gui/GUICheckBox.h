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

#ifndef CORE_GUI_GUICHECKBOX_H_
#define CORE_GUI_GUICHECKBOX_H_

#include "GUIComponent.h"

/***************************************************************************************************
 * The GUICheckBox class
 ***************************************************************************************************/

class GUICheckBox : public GUIComponent {
public:
	std::string text;
	bool checked;

	GUICheckBox(GUIComponentRenderer* renderer);
	GUICheckBox(std::vector<Colour> colours, float width, float height);
	GUICheckBox(std::vector<Texture*> textures, float width, float height);
	GUICheckBox(std::vector<Texture*> textures, std::vector<Colour> colours, float width, float height);
	GUICheckBox(std::string text, std::vector<Colour> colours, float width, float height);
	GUICheckBox(std::string text, std::vector<Texture*> textures, float width, float height);
	GUICheckBox(std::string text, std::vector<Texture*> textures, std::vector<Colour> colours, float width, float height);

	virtual void updateComponent() override;
	virtual void renderComponent() override { renderTextAtCentre(text, Vector2f(((renderer->font->getWidth(text) / 2) + (getWidth() / 2)) + 4, 0)); }
	virtual void componentOnClicked() override { checked = ! checked; }

	inline void setText(std::string text) { this->text = text; }
	inline std::string getText() { return text; }
};

/***************************************************************************************************/

#endif /* CORE_GUI_GUIBUTTON_H_ */
