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

#ifndef CORE_GUI_GUIRADIOCHECKBOX_H_
#define CORE_GUI_GUIRADIOCHECKBOX_H_

#include "GUICheckBox.h"

/***************************************************************************************************
 * The GUIRadioCheckBox class
 ***************************************************************************************************/

class GUIRadioCheckBox : public GUICheckBox {
public:
	GUIRadioCheckBox(GUIComponentRenderer* renderer) : GUICheckBox(renderer) {}
	GUIRadioCheckBox(std::vector<Colour> colours, float width, float height) :
		GUICheckBox(colours, width, height) {}
	GUIRadioCheckBox(std::vector<Texture*> textures, float width, float height) :
		GUICheckBox(textures, width, height) {}
	GUIRadioCheckBox(std::vector<Texture*> textures, std::vector<Colour> colours, float width, float height) :
		GUICheckBox(textures, colours, width, height) {}
	GUIRadioCheckBox(std::string text, std::vector<Colour> colours, float width, float height) :
		GUICheckBox(text, colours, width, height) {}
	GUIRadioCheckBox(std::string text, std::vector<Texture*> textures, float width, float height) :
		GUICheckBox(text, textures, width, height) {}
	GUIRadioCheckBox(std::string text, std::vector<Texture*> textures, std::vector<Colour> colours, float width, float height) :
		GUICheckBox(text, textures, colours, width, height) {}

	virtual void componentOnClicked() override;
};

/***************************************************************************************************/

#endif /* CORE_GUI_GUIBUTTON_H_ */
