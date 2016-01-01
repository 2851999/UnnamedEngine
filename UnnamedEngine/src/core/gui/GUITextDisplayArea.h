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

#ifndef CORE_GUI_GUITEXTDISPLAYAREA_H_
#define CORE_GUI_GUITEXTDISPLAYAREA_H_

#include "GUIComponent.h"

/***************************************************************************************************
 * The GUITextDisplayArea class
 ***************************************************************************************************/

class GUITextDisplayArea : public GUIComponent {
private:
	/* The text */
	std::vector<std::string> m_text;
public:
	/* The constructors */
	GUITextDisplayArea(std::string text, float width) :
		GUIComponent(NULL) {
		setWidth(width);
		calculateText(text);
	}
	GUITextDisplayArea(std::string text, Font* font, float width) :
		GUIComponent(NULL) {
		renderer->font = font;
		setWidth(width);
		calculateText(text);
	}

	/* Sets up the text to be displayed */
	void calculateText(std::string text);

	/* The render method */
	void renderComponent() override;

	/* The setters and getters */
	inline void setText(std::string text) { calculateText(text); }
	std::string getText();
};

/***************************************************************************************************/

#endif /* CORE_GUI_GUITEXTDISPLAYAREA_H_ */
