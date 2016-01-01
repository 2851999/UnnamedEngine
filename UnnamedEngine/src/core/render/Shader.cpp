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

#include "../../utils/FileUtils.h"
#include "Shader.h"
#include "../Matrix.h"

/***************************************************************************************************
 * Define the Shader class's methods
 ***************************************************************************************************/

Shader::Shader(GLuint vertexShader, GLuint fragmentShader) {
	m_program = glCreateProgram();
	m_vertexShader = vertexShader;
	m_fragmentShader = fragmentShader;

	attach(m_vertexShader);
	attach(m_fragmentShader);
}

Shader::~Shader() {
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
	glDeleteProgram(m_program);
}

void Shader::attach(GLuint shader) {
	glAttachShader(m_program, shader);
	glLinkProgram(m_program);

	GLint status = 0;
	glGetProgramiv(m_program, GL_LINK_STATUS, &status);
	if (! status) {
		GLchar error[1024];
		glGetProgramInfoLog(m_program, sizeof(error), NULL, error);
		logError("Error linking shader " + to_string(error));
	}

	glValidateProgram(m_program);
}

void Shader::use() {
	glUseProgram(m_program);
}

void Shader::stopUsing() {
	glUseProgram(0);
}

void Shader::detach(GLuint shader) {
	glDetachShader(m_program, shader);
}

void Shader::addUniform(std::string id, std::string name) {
	GLint location = glGetUniformLocation(m_program, name.c_str());
	if (location == -1)
		logWarning("The uniform with the name '" + name + "' could not be found");
	m_uniforms.insert(std::pair<std::string, GLint>(id, location));
}

void Shader::addAttribute(std::string id, std::string name) {
	GLint location = glGetAttribLocation(m_program, name.c_str());
	if (location == -1)
		logWarning("The attribute with the name '" + name + "' could not be found");
	m_attributes.insert(std::pair<std::string, GLint>(id, location));
}

std::string Shader::loadShaderData(const char* path, const char* fileName) {
	std::ifstream input;
	std::string   output;
	std::string   current;

	input.open((std::string(path) + std::string(fileName)).c_str());

	if (input.is_open()) {
		while (input.good()) {
			getline(input, current);
			if (current.find("#") == std::string::npos)
				output.append(current + "\n");
			else if (current.find("#include") != std::string::npos) {
				std::string includeFile = split_string_last(current, ' ');
				output += loadShaderData(path, includeFile.substr(1, includeFile.size() - 2).c_str());
			}
		}
		input.close();
	} else
		logError("Unable to read the file '" + to_string(fileName) + "'");

	return output;
}

GLuint Shader::loadShaderFromPath(const char* path, const char* fileName, GLenum type) {
	return Shader::loadShader(Shader::loadShaderData(path, fileName), type);
}

GLuint Shader::loadShader(std::string data, GLenum type) {
	GLuint shader = glCreateShader(type);

	const GLchar* sdata[1];
	sdata[0] = data.c_str();
	GLint length[1];
	length[0] = data.length();

	glShaderSource(shader, 1, sdata, length);
	glCompileShader(shader);
	GLint status = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (! status) {
		GLchar error[1024];
		glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		logError("Error compiling shader " + to_string(error));
	}
	return shader;
}

void Shader::setUniform(std::string name, Matrix3f value) { glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &(value.m_values[0][0])); }
void Shader::setUniform(std::string name, Matrix4f value) { glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &(value.m_values[0][0])); }

/***************************************************************************************************/

/***************************************************************************************************
 * The RenderShader class
 ***************************************************************************************************/

RenderShader::~RenderShader() {
	for (unsigned int a = 0; a < m_shaders.size(); a++)
		delete m_shaders.at(a);
}

/***************************************************************************************************/
