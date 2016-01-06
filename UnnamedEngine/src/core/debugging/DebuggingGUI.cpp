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

#include "DebuggingGUI.h"

#include "../render/Renderer.h"

/***************************************************************************************************
 * The DebuggingGUI class
 ***************************************************************************************************/

void DebuggingGUI::processCommand(std::string command) {
	std::vector<std::string> split = split_string(command, ' ');

	if (split[0] == "print") {
		if (split[1] == "text") {
			for (unsigned int n = 2; n < split.size(); n++) {
				std::cout << split[n];
				if (n != split.size() - 1)
					std::cout << " ";
			}
			std::cout << std::endl;
		} else if (split[1] == "version") {
			std::cout << to_string(Settings::ENGINE_NAME) + " " + to_string(Settings::ENGINE_VERSION) + " (" + to_string(Settings::ENGINE_VERSION_NAME) + ") " + to_string(Settings::ENGINE_BUILD) + " " + to_string(Settings::ENGINE_DATE) << std::endl;
		}
	} else if (split[0] == "reload") {
		if (split[1] == "shaders") {
			Renderer::initialiseShaders();
		}
	}
}

/***************************************************************************************************/
