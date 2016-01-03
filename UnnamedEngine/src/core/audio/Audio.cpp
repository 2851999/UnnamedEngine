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

#include <cstdio>

#include "Audio.h"
#include "../BaseEngine.h"

/***************************************************************************************************
 * The AudioLoader class
 ***************************************************************************************************/

AudioData* AudioLoader::loadAudio(const char* path) {
	std::string value = string_toLowerCase(to_string(path));
	//Check the file type
	if (string_endsWith(value, ".wav"))
		return loadWave(path);
	else
		return NULL;
}

AudioData* AudioLoader::loadWave(const char* path) {
	//Define the needed values
	FILE* audioFile = NULL;
	Wave_RIFF   waveRiff;
	Wave_Format waveFormat;
	Wave_Data   waveData;

	AudioData* data = new AudioData();

	audioFile = fopen(path, "rb");

	fread(&waveRiff, sizeof(Wave_RIFF), 1, audioFile);

    if (waveRiff.chunkID[0] != 'R' ||
    	waveRiff.chunkID[1] != 'I' ||
		waveRiff.chunkID[2] != 'F' ||
		waveRiff.chunkID[3] != 'F') {

    	logError("Wave file: " + to_string(path) + " has an invalid RIFF header");

    	return NULL;
    }

    if (waveRiff.format[0] != 'W' ||
		waveRiff.format[1] != 'A' ||
		waveRiff.format[2] != 'V' ||
		waveRiff.format[3] != 'E') {

	    logError("Wave file: " + to_string(path) + " has an invalid WAVE header");

	    return NULL;
	}

    fread(&waveFormat, sizeof(Wave_Format), 1, audioFile);

    if (waveFormat.subChunkID[0] != 'f' ||
    	waveFormat.subChunkID[1] != 'm' ||
		waveFormat.subChunkID[2] != 't' ||
		waveFormat.subChunkID[3] != ' ') {

	    logError("Wave file: " + to_string(path) + " has an invalid format header");

	    return NULL;
	}

    //Check for any extra parameters
    if (waveFormat.subChunkSize > 16)
    	fseek(audioFile, sizeof(short), SEEK_CUR);

    fread(&waveData, sizeof(Wave_Data), 1, audioFile);

    if (waveData.subChunkID[0] != 'd' ||
    	waveData.subChunkID[1] != 'a' ||
		waveData.subChunkID[2] != 't' ||
		waveData.subChunkID[3] != 'a') {

	    logError("Wave file: " + to_string(path) + " has an invalid data header");

	    return NULL;
	}

    data->data = new unsigned char[waveData.subChunk2Size];

    if (! fread(data->data, waveData.subChunk2Size, 1, audioFile))
    	return NULL;

    data->size = waveData.subChunk2Size;
    data->sampleRate = waveFormat.sampleRate;

    if (waveFormat.numChannels == 1) {
    	if (waveFormat.bitsPerSample == 8)
    		data->format = AL_FORMAT_MONO8;
    	else if (waveFormat.bitsPerSample == 16)
    		data->format = AL_FORMAT_MONO16;
    } else if (waveFormat.numChannels == 2) {
    	if (waveFormat.bitsPerSample == 8)
    		data->format = AL_FORMAT_STEREO8;
    	else if (waveFormat.bitsPerSample == 16)
    		data->format = AL_FORMAT_STEREO16;
    }

    fclose(audioFile);

    return data;
}

/***************************************************************************************************/

/***************************************************************************************************
 * The AudioSource class
 ***************************************************************************************************/

AudioSource::AudioSource(AudioData* data, unsigned int type) {
	if (AudioManager::hasContext()) {
		m_type = type;
		alGenSources(1, &m_sourceHandle);
		alGenBuffers(1, &m_bufferHandle);
		m_pitch = 1.0f;
		updateVolume();
		m_loop = false;

		alBufferData(m_bufferHandle, data->format, (void*) data->data, data->size, data->sampleRate);
		alSourcei(m_sourceHandle, AL_BUFFER, m_bufferHandle);

		AudioManager::add(this);
	}
}

void AudioSource::updateVolume() {
	if (m_type == TYPE_SOUND_EFFECT)
		m_gain = ((float) BaseEngine::current->getSettings()->getAudioSoundEffectVolume()) / 100.0f;
	else if (m_type == TYPE_MUSIC)
		m_gain = ((float) BaseEngine::current->getSettings()->getAudioMusicVolume()) / 100.0f;
	else {
		m_gain = 1.0f;
	}
}

void AudioSource::update() {
	if (AudioManager::hasContext()) {
		//Get all of the needed values
		Vector3f sourcePosition = getPosition();
		//Vector3f sourceRotation = this.getRotation();
		Vector3f sourceVelocity = getVelocity();
		//Update all of the source values
		alSource3f(m_sourceHandle, AL_POSITION, sourcePosition.getX(), sourcePosition.getY(), sourcePosition.getZ());
		//AL10.alSource3f(this.sourceHandle, AL10.AL_ORIENTATION, sourceRotation.x, sourceRotation.y, sourceRotation.z);
		alSource3f(m_sourceHandle, AL_VELOCITY, sourceVelocity.getX(), sourceVelocity.getY(), sourceVelocity.getZ());
		alSourcef(m_sourceHandle, AL_PITCH, m_pitch);
		alSourcef(m_sourceHandle, AL_GAIN, m_gain);
		if (m_loop)
			alSourcei(m_sourceHandle, AL_LOOPING, AL_TRUE);
		else
			alSourcei(m_sourceHandle, AL_LOOPING, AL_FALSE);
	}
}

void AudioSource::play() {
	if (AudioManager::hasContext())
		alSourcePlay(m_sourceHandle);
}

void AudioSource::stop() {
	if (AudioManager::hasContext())
		alSourceStop(m_sourceHandle);
}

void AudioSource::pause() {
	if (AudioManager::hasContext())
		alSourcePause(m_sourceHandle);
}

void AudioSource::resume() {
	if (AudioManager::hasContext())
		alSourcePlay(m_sourceHandle);
}

void AudioSource::release() {
	if (AudioManager::hasContext()) {
		alDeleteSources(1, &m_sourceHandle);
		alDeleteBuffers(1, &m_bufferHandle);
	}
}

bool AudioSource::isPlaying() {
	int value = 0;
	alGetSourcei(m_sourceHandle, AL_SOURCE_STATE, &value);
	return value == AL_PLAYING;
}

/***************************************************************************************************/

/***************************************************************************************************
 * The AudioListener class
 ***************************************************************************************************/

void AudioListener::update() {
	if (AudioManager::hasContext()) {
		//Get the needed values
		Vector3f listenerPosition = getPosition();
		Vector3f listenerRotation = getRotation();
		Vector3f listenerVelocity = getVelocity();
        float xDirection = 1.0f * (float) sin(to_radians(listenerRotation.getY()));
        float zDirection = -1.0f * (float) cos(to_radians(listenerRotation.getY()));
		//Setup OpenAL
		alListener3f(AL_POSITION, -listenerPosition.getX(), -listenerPosition.getY(), -listenerPosition.getZ());
		alListener3f(AL_VELOCITY, listenerVelocity.getX(), listenerVelocity.getY(), listenerVelocity.getZ());
		ALfloat listenerOrientation[] = { xDirection, 0.0f, zDirection, 0.0f, 1.0f, 0.0f };
		alListenerfv(AL_ORIENTATION, listenerOrientation);
	}
}

/***************************************************************************************************/

/***************************************************************************************************
 * The AudioManager class
 ***************************************************************************************************/

std::vector<AudioSource*> AudioManager::m_sources;
ALCdevice* AudioManager::device;
ALCcontext* AudioManager::context;

void AudioManager::releaseAll() {
	for (unsigned int a = 0; a < m_sources.size(); a++)
		delete m_sources.at(a);
	m_sources.clear();
}

void AudioManager::initialise() {
	device = alcOpenDevice(NULL);
	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);
}

void AudioManager::destroy() {
	releaseAll();
	alcCloseDevice(device);
	alcDestroyContext(context);
}

void AudioManager::updateVolume() {
	for (unsigned int a = 0; a < m_sources.size(); a++)
		m_sources.at(a)->updateVolume();
}

/***************************************************************************************************/
