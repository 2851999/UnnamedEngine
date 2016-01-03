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

#include "../BaseEngine.h"
#include "GUIPanel.h"

/***************************************************************************************************
 * The GUIPanel class
 ***************************************************************************************************/

GUIPanel::GUIPanel(std::string name, bool autoUpdate) {
	m_group = new GUIGroup(name);
	attach(m_group);
	if (autoUpdate)
		BaseEngine::current->add(this);
}

void GUIPanel::add(GUIComponent* component) {
	if (m_addListener)
		component->addListener(this);
	m_group->add(component);
}

void GUIPanel::setResolution(Vector2f resolution) {
	if (resolution.getX() == -1)
		m_resolution = resolution;
	else {
		float scaleWidth = resolution.getX() / m_resolution.getX();
		float scaleHeight = resolution.getY() / m_resolution.getY();
		m_resolution = resolution;
		scale(Vector2f(scaleWidth, scaleHeight));
	}
}

/***************************************************************************************************/
