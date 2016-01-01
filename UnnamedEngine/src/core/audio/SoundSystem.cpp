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

#include <algorithm>
#include "SoundSystem.h"

/***************************************************************************************************
 * The SoundSystem class
 ***************************************************************************************************/

void SoundSystem::play(std::string key) {
	AudioSource* source = getSource(key);
	source->play();
	m_playing.push_back(source);
}

void SoundSystem::pause(std::string key) {
	getSource(key)->pause();
}

void SoundSystem::resume(std::string key) {
	getSource(key)->resume();
}

void SoundSystem::stop(std::string key) {
	AudioSource* source = getSource(key);
	source->stop();
	m_playing.erase(std::remove(m_playing.begin(), m_playing.end(), source));
}

void SoundSystem::update() {
	//Update the listener
	if (m_listener != NULL)
		m_listener->update();
	//Go through the sources
	for (unsigned int a = 0; a < m_playing.size(); a++) {
		//Check to see whether the source is still playing
		if (m_playing.at(a)->isPlaying())
			//Update the source
			m_playing.at(a)->update();
		else
			m_playing.erase(m_playing.begin() + a);
	}
}

/***************************************************************************************************/
