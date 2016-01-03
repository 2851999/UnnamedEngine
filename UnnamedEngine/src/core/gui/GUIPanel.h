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

#ifndef CORE_GUI_GUIPANEL_H_
#define CORE_GUI_GUIPANEL_H_

#include "../BaseEngineLoop.h"
#include "GUIComponent.h"

/***************************************************************************************************
 * The GUIPanel class
 ***************************************************************************************************/

class GUIPanel : public Object2D, public BaseEngineLoop, public GUIComponentListener {
private:
	/* The group of components */
	GUIGroup* m_group = NULL;

	/* The initial resolution of this panel */
	Vector2f m_resolution = Vector2f(-1, -1);

	/* States whether a component listener should be added to any component */
	bool m_addListener = true;
public:
	/* The constructor */
	GUIPanel(std::string name, bool autoUpdate = false);

	/* The update and render methods */
	inline void update() override { m_group->update(); }
	inline void render() override { m_group->render(); }

	/* The method used to add a component to this panel */
	void add(GUIComponent* component);

	/* The method used to change the scale of this panel */
	inline void scale(Vector2f amount) { m_group->scale(amount); }

	/* The method used to change the resolution of the panel */
	void setResolution(Vector2f resolution);

	/* The method used to clear this panel */
	inline void clear() { m_group->clear(); }

	/* The method used to remove a component */
	inline void remove(GUIComponent* component) { m_group->remove(component); }

	/* The component listener methods */
	virtual void onMouseEnter(GUIComponent* component) override {}
	virtual void onMouseLeave(GUIComponent* component) override {}
	virtual void onClicked(GUIComponent* component) override {}
};

/***************************************************************************************************/

#endif /* CORE_GUI_GUIPANEL_H_ */
