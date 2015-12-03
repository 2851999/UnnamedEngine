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

#ifndef CORE_GUI_GUIDROPDOWNMENU_H_
#define CORE_GUI_GUIDROPDOWNMENU_H_

#include "../input/Input.h"
#include "GUIComponent.h"
#include "GUIButton.h"

/***************************************************************************************************
 * The GUIDropDownMenu class
 ***************************************************************************************************/

class GUIDropDownMenu : public GUIComponent, GUIComponentListener, InputListener {
protected:
	std::vector<GUIButton*> buttons;
	virtual void updateMenu();
public:
	GUIButton* menuButton;
	bool menuOpen;

	GUIDropDownMenu(GUIButton* button);

	virtual void updateComponent() override;
	virtual void renderComponent() override;

	virtual void onClicked(GUIComponent* component) override;
	virtual void onMouseClicked(int button) override;

	void addButton(GUIButton* button);
	void addButton(GUIButton* button, std::string name);

	inline void setOpen(bool open) { menuOpen = open; }
	inline void toggleOpen() { menuOpen = ! menuOpen; }
	inline bool isOpen() { return menuOpen; }
	inline std::vector<GUIButton*> getButtons() { return buttons; }

	Rect getMenuBounds();
};

/***************************************************************************************************/

#endif /* CORE_GUI_GUIDROPDOWNMENU_H_ */
