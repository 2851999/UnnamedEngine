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

#include "../Object.h"
#include "GUIRadioCheckBox.h"

/***************************************************************************************************
 * The GUIRadioCheckBox class
 ***************************************************************************************************/

void GUIRadioCheckBox::componentOnClicked() {
	checked = ! checked;
	if (belongsToGroup()) {
		for (unsigned int a = 0; a < group->getGroupComponents().size(); a++) {
			GUIComponent* component = group->getGroupComponents()[a];
			if (GUIRadioCheckBox* checkBox = dynamic_cast<GUIRadioCheckBox*>(component)) {
				if (checkBox != this)
					checkBox->checked = false;
			}
		}
	}
}

/***************************************************************************************************/
