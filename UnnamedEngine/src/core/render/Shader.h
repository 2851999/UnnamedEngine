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

#ifndef CORE_SHADER_H_
#define CORE_SHADER_H_

#include<windows.h>
#include<GL/GLEW/glew.h>
#include<GL/GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<vector>
#include<map>

#include "../Vector.h"
#include "../../utils/StringUtils.h"
#include "../../utils/Logging.h"

class Matrix4f;

/***************************************************************************************************
 * The Shader class stores data needed to use a shader while also providing utilities to change
 * values within it
 ***************************************************************************************************/

class Shader {
private:
	GLuint m_program        = -1;
	GLuint m_vertexShader   = -1;
	GLuint m_fragmentShader = -1;
	std::map<std::string, GLint> m_uniforms;
	std::map<std::string, GLint> m_attributes;
public:
	Shader() {}
	Shader(GLuint vertexShader, GLuint fragmentShader);
	virtual ~Shader();

	void attach(GLuint shader);
	void use();
	void stopUsing();
	void detach(GLuint shader);
	void addUniform(std::string id, std::string name);
	void addAttribute(std::string id, std::string name);
	inline GLint getUniformLocation(std::string name) {
		if (m_uniforms.count(name)) {
			return m_uniforms.at(name);
		} else {
			logError(std::string("The uniform with the name ") + name + std::string(" could not be located"));
			return -1;
		}
	}
	inline GLint getAttributeLocation(std::string name) {
		if (m_attributes.count(name)) {
			return m_attributes.at(name);
		} else {
			logError(std::string("The attribute with the name ") + name + std::string(" could not be located"));
			return -1;
		}
	}

	/* Various methods used to assign specific values */
	inline void setUniform(std::string name, int value) { glUniform1i(getUniformLocation(name), value); }
	inline void setUniform(std::string name, GLuint value) { glUniform1i(getUniformLocation(name), value); }
	inline void setUniform(std::string name, float value) { glUniform1f(getUniformLocation(name), value); }
	inline void setUniform(std::string name, Colour value) { glUniform4f(getUniformLocation(name), value.getR(), value.getG(), value.getB(), value.getA()); }
	void setUniform(std::string name, Matrix4f value);
	inline void setUniform(std::string name, Vector3f value) { glUniform3f(getUniformLocation(name), value.getX(), value.getY(), value.getZ()); }

	GLuint getProgram() { return m_program; }
	static std::string loadShaderData(const char* path, const char* fileName);
	static GLuint loadShaderFromPath(const char* path, const char* fileName,  GLenum type);
	static GLuint loadShader(std::string data, GLenum type);
};

/***************************************************************************************************/

/***************************************************************************************************
 * The RenderShader class provides a way to manage shaders for rendering
 ***************************************************************************************************/

class RenderShader {
private:
	std::vector<Shader*> m_shaders;
public:
	RenderShader() {}
	RenderShader(Shader* defaultShader) { m_shaders.push_back(defaultShader); }
	virtual ~RenderShader();
	inline void addShader(Shader* shader) { m_shaders.push_back(shader); }
	inline void removeShader(Shader* shader) { m_shaders.erase(m_shaders.end()); }
	inline Shader* getShader() { return m_shaders.back(); }
};

/***************************************************************************************************/

#endif
