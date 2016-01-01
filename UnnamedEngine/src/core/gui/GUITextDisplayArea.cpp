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

#include "GUITextDisplayArea.h"

/***************************************************************************************************
 * The GUITextDisplayArea class
 ***************************************************************************************************/

void GUITextDisplayArea::calculateText(std::string text) {
	//Split up the text
	std::vector<std::string> split = split_string(text, ' ');
	float width = getWidth();
	//Go trough the text
	for (unsigned int a = 0; a < split.size(); a++) {
		//Get the current position in the array
		int position = m_text.size() - 1;
		//Check to see whether any words have been added
		if (m_text.size() == 0)
			//Add the first word
			m_text.push_back(split[a]);
		else {
			//Check to see whether the next word can be added
			if (renderer->font->getWidth(m_text.at(position) + " " + split[a]) <= width)
				//Add the current word to the last line of text
				m_text[position] = m_text.at(position) + " " + split[a];
			else
				//Add the current word on a new line
				m_text.push_back(split[a]);
		}
	}
}

void GUITextDisplayArea::renderComponent() {
	//The current offset
	Vector2f offset;
	//Go through each line of text
	for (unsigned int a = 0; a < m_text.size(); a++) {
		//Render the current line of text
		renderText(m_text.at(a), offset);
		//Add onto the offset
		offset.setY(offset.getY() + renderer->font->getHeight(""));
	}
}

std::string GUITextDisplayArea::getText() {
	//The text
	std::string text = "";
	//Go through each line of text
	for (unsigned int a = 0; a < m_text.size(); a++)
		//Add the current line to the text
		text += m_text.at(a);
	//Return the text
	return text;
}

/***************************************************************************************************/
