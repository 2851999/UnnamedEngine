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

#ifndef CORE_SETTINGS_H_
#define CORE_SETTINGS_H_

#include <iostream>
#include "Vector.h"

/***************************************************************************************************
 * Define the default, predefined settings
 ***************************************************************************************************/

/* The raw video resolutions */

const Vector2i VIDEO_RESOLUTION_640x480   = Vector2i(640, 480);
const Vector2i VIDEO_RESOLUTION_1280x720  = Vector2i(1280, 720);
const Vector2i VIDEO_RESOLUTION_1366x768  = Vector2i(1366, 768);
const Vector2i VIDEO_RESOLUTION_1920x1080 = Vector2i(1920, 1080);
const Vector2i VIDEO_RESOLUTION_3840x2160 = Vector2i(3840, 2160);

/* The named video resolutions */
const Vector2i VIDEO_RESOLUTION_DEFAULT   = VIDEO_RESOLUTION_1280x720;
const Vector2i VIDEO_RESOLUTION_720P      = VIDEO_RESOLUTION_1280x720;
const Vector2i VIDEO_RESOLUTION_1080P     = VIDEO_RESOLUTION_1920x1080;
const Vector2i VIDEO_RESOLUTION_4K        = VIDEO_RESOLUTION_3840x2160;

/***************************************************************************************************
 * The Settings class will contain all of the data required to create
 * a window and an OpenGL context
 ***************************************************************************************************/

class Settings {
private:
	/* The values that correspond to the window */
	std::string m_window_title;
	int         m_window_width;
	int         m_window_height;
	bool        m_window_resizable;
	bool        m_window_decorated;
	bool        m_window_fullscreen;
	bool        m_window_borderless;
	bool        m_window_floating;

	/* The values that correspond to specific 'video' settings */
	bool        m_video_vsync;
	int         m_video_samples;
	int         m_video_refresh_rate;
	int         m_video_max_anisotropic_samples;
	Vector2i    m_video_resolution;
	bool		m_video_deferred_rendering;

	/* The values that correspond to specific 'audio' settings */
	unsigned int m_audio_volume_sound_effect;
	unsigned int m_audio_volume_music;

	/* The values that correspond to specific 'input' settings */
	bool        m_input_mouse_events_repeat;
	bool        m_input_keyboard_events_repeat;

	/* The values that correspond to specific 'debugging' settings */
	bool		m_debugging_show_information;
	bool		m_debugging_show_deferred_rendering_buffers;
public:
	static const char* ENGINE_NAME;
	static const char* ENGINE_VERSION;
	static const char* ENGINE_VERSION_NAME;
	static const char* ENGINE_DATE;
	static const char* ENGINE_BUILD;

	/* The constructor sets the default settings */
	Settings() {
		setDefault();
	}

	/* The method that sets the default settings */
	void setDefault() {
		m_window_title       = std::string(ENGINE_NAME) + " " + std::string(ENGINE_VERSION) + " (" + std::string(ENGINE_VERSION_NAME) + ")";
		m_window_resizable   = false;
		m_window_decorated   = true;
		m_window_fullscreen  = false;
		m_window_borderless  = false;
		m_window_floating    = false;

		m_video_vsync        = true;
		m_video_samples      = 0;
		m_video_refresh_rate = 60;
		m_video_max_anisotropic_samples = 0;
		m_video_resolution   = VIDEO_RESOLUTION_DEFAULT;
		m_video_deferred_rendering = false;

		m_audio_volume_sound_effect = 100;
		m_audio_volume_music = 100;

		m_input_mouse_events_repeat = false;
		m_input_keyboard_events_repeat = true;

		m_debugging_show_information = true;
		m_debugging_show_deferred_rendering_buffers = true;
	}

	/* Define all of the methods used to assign and get values stored
	 * in this class */
	inline void setWindowTitle(std::string title)    { m_window_title       = title;      }
	inline void setWindowWidth(int width)            { m_window_width       = width;      }
	inline void setWindowHeight(int height)          { m_window_height      = height;     }
	inline void setWindowSize(int width, int height) { m_window_width       = width;
	                                                   m_window_height      = height;     }
	inline void setWindowResizable(bool resizable)   { m_window_resizable   = resizable;  }
	inline void setWindowDecorated(bool decorated)   { m_window_decorated   = decorated;  }
	inline void setWindowFullscreen(bool fullscreen) { m_window_fullscreen  = fullscreen; }
	inline void setWindowBorderless(bool borderless) { m_window_borderless  = borderless; }
	inline void setWindowFloating(bool floating)     { m_window_floating    = floating;   }

	inline void setVideoVSync(bool vSync)            { m_video_vsync        = vSync;      }
	inline void setVideoSamples(int samples)         { m_video_samples      = samples;    }
	inline void setVideoRefreshRate(int refreshRate) { m_video_refresh_rate = refreshRate; }
	inline void setVideoMaxAnisotropicSamples(int maxAnisotropicSamples) { m_video_max_anisotropic_samples = maxAnisotropicSamples; }
	inline void setVideoResolution(Vector2i videoResolution)             { m_video_resolution              = videoResolution;       }
	inline void setVideoDeferredRendering(bool videoDeferredRendering)   { m_video_deferred_rendering      = videoDeferredRendering; }

	inline void setAudioSoundEffectVolume(unsigned int soundEffectVolume) { m_audio_volume_sound_effect = soundEffectVolume; }
	inline void setAudioMusicVolume(unsigned int musicVolume) { m_audio_volume_music = musicVolume; }

	inline void setMouseEventsRepeat(bool mouseEventsRepeat)             { m_input_mouse_events_repeat = mouseEventsRepeat; }
	inline void setKeyboardEventsRepeat(bool keyboardEventsRepeat)             { m_input_keyboard_events_repeat = keyboardEventsRepeat; }

	inline void setDebggingShowInformation(bool debuggingShowInformation) { m_debugging_show_information = debuggingShowInformation; }
	inline void setDebuggingShowDeferredRenderingBuffers(bool debuggingShowDeferredRenderingBuffers) { m_debugging_show_deferred_rendering_buffers = debuggingShowDeferredRenderingBuffers; }

	inline std::string getWindowTitle()                    { return m_window_title;            }
	inline int         getWindowWidth()                    { return m_window_width;            }
	inline int         getWindowHeight()                   { return m_window_height;           }
	inline bool        getWindowResizable()                { return m_window_resizable;        }
	inline bool        getWindowDecorated()                { return m_window_decorated;        }
	inline bool        getWindowFullscreen()               { return m_window_fullscreen;       }
	inline bool        getWindowBorderless()               { return m_window_borderless;       }
	inline bool        getWindowFloating()                 { return m_window_floating;         }

	inline bool        getVideoVSync()                     { return m_video_vsync;             }
	inline int         getVideoSamples()                   { return m_video_samples;           }
	inline int         getVideoRefreshRate()               { return m_video_refresh_rate;      }
	inline int         getVideoMaxAnisotropicSamples()     { return m_video_max_anisotropic_samples; }
	inline Vector2i    getVideoResolution()                { return m_video_resolution;        }
	inline bool		   getVideoDeferredRendering()         { return m_video_deferred_rendering; }

	inline unsigned int getAudioSoundEffectVolume() { return m_audio_volume_sound_effect; }
	inline unsigned int getAudioMusicVolume() { return m_audio_volume_music; }

	inline bool        getMouseEventsRepeat()              { return m_input_mouse_events_repeat; }
	inline bool        getKeyboardEventsRepeat()              { return m_input_keyboard_events_repeat; }

	inline bool		   getDebuggingShowInformation()       { return m_debugging_show_information; }
	inline bool		   getDebuggingShowDeferredRenderingBuffers() { return m_debugging_show_deferred_rendering_buffers; }
};

/***************************************************************************************************/

#endif
