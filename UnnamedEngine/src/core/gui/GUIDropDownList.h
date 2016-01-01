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

#ifndef CORE_GUI_GUIDROPDOWNLIST_H_
#define CORE_GUI_GUIDROPDOWNLIST_H_

#include "GUIDropDownMenu.h"

/***************************************************************************************************
 * The GUIDropDownList class
 ***************************************************************************************************/

class GUIDropDownList : public GUIDropDownMenu {
public:
	RenderableObject2D* overlay;
	Texture* overlayTexture;

	GUIDropDownList(GUIButton* menuButton);
	GUIDropDownList(GUIButton* menuButton, Texture* overlayTexture);

	void setupOverlay(Texture* texture);

	virtual void renderComponent() override;
	virtual void onClicked(GUIComponent* component) override;
};

/***************************************************************************************************/

#endif /* CORE_GUI_GUIDROPDOWNLIST_H_ */
