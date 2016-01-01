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

#ifndef CORE_TEXTURE_H_
#define CORE_TEXTURE_H_

#include <windows.h>
#include <GL/GLEW/glew.h>
#include "../utils/Logging.h"

/***************************************************************************************************
 * The TextureParameters class
 ***************************************************************************************************/

class TextureParameters {
private:
	GLuint m_target;
	GLuint m_filter;
	GLuint m_clamp;
	bool m_shouldClamp;
public:
	static GLuint DEFAULT_TARGET;
	static GLuint DEFAULT_FILTER;
	static GLuint DEFAULT_CLAMP;
	static bool DEFAULT_SHOULD_CLAMP;
	TextureParameters() {
		m_target = DEFAULT_TARGET;
		m_filter = DEFAULT_FILTER;
		m_clamp = DEFAULT_CLAMP;
		m_shouldClamp = DEFAULT_SHOULD_CLAMP;
	}
	TextureParameters(GLuint target) {
		m_target = target;
		m_filter = DEFAULT_FILTER;
		m_clamp = DEFAULT_CLAMP;
		m_shouldClamp = DEFAULT_SHOULD_CLAMP;
	}
	TextureParameters(GLuint target, bool shouldClamp) {
		m_target = target;
		m_filter = DEFAULT_FILTER;
		m_clamp = DEFAULT_CLAMP;
		m_shouldClamp = shouldClamp;
	}
	TextureParameters(GLuint target, GLuint filter, bool shouldClamp) {
		m_target = target;
		m_filter = filter;
		m_clamp = DEFAULT_CLAMP;
		m_shouldClamp = shouldClamp;
	}
	TextureParameters(GLuint target, GLuint filter, GLuint clamp) {
		m_target = target;
		m_filter = filter;
		m_clamp = clamp;
		m_shouldClamp = true;
	}
	TextureParameters(GLuint target, GLuint filter, GLuint clamp, bool shouldClamp) {
		m_target = target;
		m_filter = filter;
		m_clamp = clamp;
		m_shouldClamp = shouldClamp;
	}
	void apply(GLuint texture, bool bind, bool unbind);
	inline void apply(GLuint texture, bool unbind) { apply(texture, true, unbind); }
	inline void apply(GLuint texture) { apply(texture, true, false); }

	inline TextureParameters setTarget(GLuint target) { m_target = target; return (*this); }
	inline TextureParameters setFilter(GLuint filter) { m_filter = filter; return (*this); }
	inline TextureParameters setClamp(GLuint clamp) { m_clamp = clamp; return (*this); }
	inline TextureParameters setShouldClamp(bool shouldClamp) { m_shouldClamp = shouldClamp; return (*this); }
	inline GLuint getTarget() { return m_target; }
	inline GLuint getFilter() { return m_filter; }
	inline GLuint getClamp() { return m_clamp; }
	inline bool shouldClamp() { return m_shouldClamp; }
};

/***************************************************************************************************/

/***************************************************************************************************
 * The Texture class
 ***************************************************************************************************/

class Texture {
protected:
	GLuint m_texture;
	int m_width;
	int m_height;
	int m_numComponents;
	TextureParameters m_parameters;
public:
	float top;
	float bottom;
	float left;
	float right;
	Texture() {
		glGenTextures(1, &m_texture);
		m_width = 0;
		m_height = 0;
		m_numComponents = 0;
		top = 0.0f;
		bottom = 1.0f;
		left = 0.0f;
		right = 1.0f;
	}
	Texture(TextureParameters parameters) {
		glGenTextures(1, &m_texture);
		m_width = 0;
		m_height = 0;
		m_numComponents = 0;
		top = 0.0f;
		bottom = 1.0f;
		left = 0.0f;
		right = 1.0f;
		m_parameters = parameters;
	}
	Texture(GLuint texture) {
		m_texture = texture;
		m_width = 0;
		m_height = 0;
		m_numComponents = 0;
		top = 0.0f;
		bottom = 1.0f;
		left = 0.0f;
		right = 1.0f;
	}
	Texture(GLuint texture, TextureParameters parameters) {
		m_texture = texture;
		m_width = 0;
		m_height = 0;
		m_numComponents = 0;
		top = 0.0f;
		bottom = 1.0f;
		left = 0.0f;
		right = 1.0f;
		m_parameters = parameters;
	}
	Texture(int width, int height) {
		glGenTextures(1, &m_texture);
		m_width = width;
		m_height = height;
		m_numComponents = 0;
		top = 0.0f;
		bottom = 1.0f;
		left = 0.0f;
		right = 1.0f;
	}

	Texture(int width, int height, TextureParameters parameters) {
		glGenTextures(1, &m_texture);
		m_width = width;
		m_height = height;
		m_numComponents = 0;
		top = 0.0f;
		bottom = 1.0f;
		left = 0.0f;
		right = 1.0f;
		m_parameters = parameters;
	}

	inline void applyParameters() {
		if (m_texture != 0)
			m_parameters.apply(m_texture);
	}

	inline void applyParameters(bool unbind) {
		if (m_texture != 0)
			m_parameters.apply(m_texture, unbind);
	}

	inline void applyParameters(bool bind, bool unbind) {
		if (m_texture != 0)
			m_parameters.apply(m_texture, bind, unbind);
	}

	inline void bind() { glBindTexture(m_parameters.getTarget(), m_texture); }
	inline void unbind() { glBindTexture(m_parameters.getTarget(), 0); }

	inline void release() {
		glDeleteTextures(1, &m_texture);
	}

	inline void setParameters(TextureParameters parameters) { m_parameters = parameters; }
	inline void setWidth(int width) { m_width = width; }
	inline void setHeight(int height) { m_height = height; }
	inline void setSize(int width, int height) { m_width = width; m_height = height; }
	inline void setNumComponents(int numComponents) { m_numComponents = numComponents; }
	inline GLuint getTexture() { return m_texture; }
	inline TextureParameters getParameters() { return m_parameters; }
	inline int getWidth() { return m_width; }
	inline int getHeight() { return m_height; }
	inline int getNumComponents() { return m_numComponents; }
	inline bool hasTexture() { return m_texture != 0; }

	static Texture* loadTexture(const char* path, TextureParameters parameters, bool applyParameters);
	inline static Texture* loadTexture(const char* path) { return loadTexture(path, TextureParameters(), true); }
};

/***************************************************************************************************/

/***************************************************************************************************
 * The RenderTexture class
 ***************************************************************************************************/

class RenderTexture : public Texture {
private:
	/* The values needed to define this texture */
	int m_internalFormat;
	int m_format;
	int m_attachment;
	int m_type;

public:
	/* The constructor */
	RenderTexture(int width, int height, int internalFormat, int format, int attachment, int type, TextureParameters parameters) : Texture(width, height, parameters),
				m_internalFormat(internalFormat), m_format(format), m_attachment(attachment), m_type(type) {
		glBindTexture(m_parameters.getTarget(), m_texture);
		glTexImage2D(m_parameters.getTarget(), 0, m_internalFormat, m_width, m_height, 0, m_format, m_type, 0);

		m_parameters.apply(m_texture, false, false);
	}

	/* The setters and getters */
	inline void setInternalFormat(int internalFormat) { m_internalFormat = internalFormat; }
	inline void setFormat(int format)                 { m_format = format; }
	inline void setAttachment(int attachment)         { m_attachment = attachment; }
	inline void setType(int type)                     { m_type = type; }

	inline int getInternalFormat()                    { return m_internalFormat; }
	inline int getFormat()                            { return m_format; }
	inline int getAttachment()                        { return m_attachment; }
	inline int getType()                              { return m_type; }
};

/***************************************************************************************************/


#endif /* CORE_TEXTURE_H_ */
