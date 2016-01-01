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

#ifndef CORE_AUDIO_AUDIO_H_
#define CORE_AUDIO_AUDIO_H_

#include <AL/al.h>
#include <AL/alc.h>

#include "../Object.h"

/***************************************************************************************************
 * The AudioObject class
 ***************************************************************************************************/

class AudioObject {
private:
	/* The linked object (if any ) */
	Object3D* m_attachedObject = NULL;
public:
	/* The position, rotation, and velocity of this object */
	Vector3f position;
	Vector3f rotation;
	Vector3f velocity;

	/* The default constructor */
	AudioObject() {}

	/* The various other constructors */
	AudioObject(Vector2f position) {
		this->position = Vector3f(position, 0);
	}

	AudioObject(Vector3f position) : position(position) {}
	AudioObject(Vector3f position, Vector3f rotation) : position(position), rotation(rotation) {}
	AudioObject(Vector3f position, Vector3f rotation, Vector3f velocity) : position(position), rotation(rotation), velocity(velocity) {}

	AudioObject(Object3D* object) : m_attachedObject(object) {}

	/* The setters and getters */
	inline void setPosition(Vector2f position) { this->position = Vector3f(position, 0); }
	inline void setPosition(Vector3f position) { this->position = position; }
	inline void setPosition(float x, float y)  { position = Vector3f(x, y, 0); }
	inline void setPosition(float x, float y, float z) { position = Vector3f(x, y, z); }

	inline void setRotation(Vector3f rotation) { this->rotation = rotation; }
	inline void setRotation(float x, float y, float z) { rotation = Vector3f(x, y, z); }

	inline void setVelocity(Vector2f velocity) { this->velocity = Vector3f(velocity, 0); }
	inline void setVelocity(Vector3f velocity) { this->velocity = velocity; }
	inline void setVelocity(float x, float y)  { velocity = Vector3f(x, y, 0); }
	inline void setVelocity(float x, float y, float z) { velocity = Vector3f(x, y, z); }

	inline void attachObject(Object3D* object) { m_attachedObject = object; }

	inline Vector3f getPosition() {
		if (m_attachedObject != NULL)
			return m_attachedObject->getPosition() + position;
		else
			return position;
	}

	inline Vector3f getRotation() {
		if (m_attachedObject != NULL)
			return m_attachedObject->getRotation() + rotation;
		else
			return rotation;
	}

	inline Vector3f getVelocity() {
		return velocity;
	}
};

/***************************************************************************************************/

/***************************************************************************************************
 * The AudioData struct
 ***************************************************************************************************/

struct AudioData {
	ALsizei size;
	ALsizei sampleRate;
	ALenum  format;
	unsigned char* data;
};

/***************************************************************************************************/

/***************************************************************************************************
 * The AudioLoader class
 ***************************************************************************************************/

class AudioLoader {
private:
	/* Holds the RIFF data */
	struct Wave_RIFF {
		char chunkID[4];
		long chumkSize;
		char format[4];
	};
	/* Holds the format data */
	struct Wave_Format {
		char subChunkID[4];
		long subChunkSize;
		short audioFormat;
		short numChannels;
		long sampleRate;
		long byteRate;
		short blockAlign;
		short bitsPerSample;
	};
	/* Holds the actual sound data */
	struct Wave_Data {
		char subChunkID[4];
		long subChunk2Size;
	};

public:
	/* The method used to load a Wave file */
	static AudioData* loadWave(const char* path);
};

/***************************************************************************************************
 * The AudioSource class
 ***************************************************************************************************/

class AudioSource : public AudioObject {
private:
	GLuint m_sourceHandle = 0;
	GLuint m_bufferHandle = 0;

	unsigned int m_type = 0;

	float m_pitch = 0;
	float m_gain  = 0;

	bool m_loop = false;
public:
	static const unsigned int TYPE_SOUND_EFFECT = 1;
	static const unsigned int TYPE_MUSIC        = 2;

	/* The constructors */
	AudioSource(AudioData* data, unsigned int type);
	AudioSource(AudioData* data, unsigned int type, Vector2f position) : AudioSource(data, type) {
		setPosition(position);
	}
	AudioSource(AudioData* data, unsigned int type, Vector3f position) : AudioSource(data, type) {
		setPosition(position);
	}

	virtual ~AudioSource() {
		release();
	}

	void updateVolume();

	void update();

	/* Various audio related methods */
	void play();
	void stop();
	void pause();
	void resume();
	void release();

	/* The setters and getters */
	inline void setPitch(float pitch) { m_pitch = pitch; }
	inline void setGain(float gain) { m_gain = gain; }
	inline void setLoop(bool loop) { m_loop = loop; }
	inline float getPitch() { return m_pitch; }
	inline float getGain() { return m_gain; }
	inline bool doesLoop() { return m_loop; }
	bool isPlaying();
};

/***************************************************************************************************/

/***************************************************************************************************
 * The AudioListener class
 ***************************************************************************************************/

class AudioListener : public AudioObject {
public:
	/* The default constructor */
	AudioListener() {}

	/* The other constructors */
	AudioListener(Object3D* object) : AudioObject(object) {}
	AudioListener(Vector2f position) : AudioObject(position) {}
	AudioListener(Vector3f position) : AudioObject(position) {}

	/* The method used to update this listener */
	void update();
};

/***************************************************************************************************/

/***************************************************************************************************
 * The AudioManager class
 ***************************************************************************************************/

class AudioManager {
private:
	/* All of the created audio sources */
	static std::vector<AudioSource*> m_sources;
public:
	/* The audio context and device */
	static ALCdevice* device;
	static ALCcontext* context;

	static inline void add(AudioSource* source) { m_sources.push_back(source); }
	static void releaseAll();

	static void initialise();
	static void destroy();
	static void updateVolume();

	static inline bool hasContext() { return context != NULL; }
};

/***************************************************************************************************/

#endif /* CORE_AUDIO_AUDIO_H_ */
