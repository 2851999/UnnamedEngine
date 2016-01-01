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

#ifndef CORE_AUDIO_SOUNDSYSTEM_H_
#define CORE_AUDIO_SOUNDSYSTEM_H_

#include "Audio.h"

/***************************************************************************************************
 * The SoundSystem class
 ***************************************************************************************************/

class SoundSystem {
private:
	/* The main listener */
	AudioListener* m_listener = NULL;

	/* The list of audio sources */
	std::map<std::string, AudioSource*> m_sources;

	/* The list of audio sources currently playing */
	std::vector<AudioSource*> m_playing;

public:
	/* The default constructor */
	SoundSystem() {}

	/* The methods used to create a listener */
	inline void createListener() { m_listener = new AudioListener(); }
	inline void createListener(Object3D* object) { m_listener = new AudioListener(object); }
	inline void createListener(Vector2f position) { m_listener = new AudioListener(position); }
	inline void createListener(Vector3f position) { m_listener = new AudioListener(position); }

	/* The methods used to add an audio source */
	inline void addSource(std::string key, AudioSource* source) { m_sources.insert(std::pair<std::string, AudioSource*>(key, source)); }
	inline void addSource(std::string key, AudioData* data, unsigned int type) { addSource(key, new AudioSource(data, type)); }
	inline void addSource(std::string key, AudioData* data, unsigned int type, Vector2f position) { addSource(key, new AudioSource(data, type, position)); }
	inline void addSource(std::string key, AudioData* data, unsigned int type, Vector3f position) { addSource(key, new AudioSource(data, type, position)); }

	inline void addSoundEffect(std::string key, AudioData* data) { addSource(key, new AudioSource(data, AudioSource::TYPE_SOUND_EFFECT)); }
	inline void addSoundEffect(std::string key, AudioData* data, Vector2f position) { addSource(key, new AudioSource(data, AudioSource::TYPE_SOUND_EFFECT, position)); }
	inline void addSoundEffect(std::string key, AudioData* data, Vector3f position) { addSource(key, new AudioSource(data, AudioSource::TYPE_SOUND_EFFECT, position)); }
	inline void addMusic(std::string key, AudioData* data) { addSource(key, new AudioSource(data, AudioSource::TYPE_MUSIC)); }
	inline void addMusic(std::string key, AudioData* data, Vector2f position) { addSource(key, new AudioSource(data, AudioSource::TYPE_MUSIC, position)); }
	inline void addMusic(std::string key, AudioData* data, Vector3f position) { addSource(key, new AudioSource(data, AudioSource::TYPE_MUSIC, position)); }

	/* The methods used to play, pause, resume and stop playing audio */
	void play(std::string key);
	void pause(std::string key);
	void resume(std::string key);
	void stop(std::string key);

	inline void playAsSoundEffect(std::string key, AudioData* data) {
		addSoundEffect(key, data);
		play(key);
	}

	inline void playAsSoundEffect(std::string key, AudioData* data, Vector2f position) {
		addSoundEffect(key, data, position);
		play(key);
	}

	inline void playAsSoundEffect(std::string key, AudioData* data, Vector3f position) {
		addSoundEffect(key, data, position);
		play(key);
	}

	inline void playAsMusic(std::string key, AudioData* data) {
		addMusic(key, data);
		play(key);
	}

	inline void playAsMusic(std::string key, AudioData* data, Vector2f position) {
		addMusic(key, data, position);
		play(key);
	}

	inline void playAsMusic(std::string key, AudioData* data, Vector3f position) {
		addMusic(key, data, position);
		play(key);
	}

	/* The method used to update the positions of all of the objects in this sound system that are currently playing */
	void update();

	/* The method used to get an AudioSource given its key */
	AudioSource* getSource(std::string key) {
		return m_sources.at(key);
	}
};

/***************************************************************************************************/

#endif /* CORE_AUDIO_SOUNDSYSTEM_H_ */