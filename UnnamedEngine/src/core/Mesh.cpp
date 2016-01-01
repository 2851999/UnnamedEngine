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

#include<windows.h>
#include<GL/GLEW/glew.h>
#include<GL/GLFW/glfw3.h>

#include "Mesh.h"
#include "render/Renderer.h"

/***************************************************************************************************
 * The Mesh class
 ***************************************************************************************************/
MeshRenderData::MeshRenderData(MeshData* data, std::string shaderType) {
	m_shaderType = shaderType;
	setup(data, true);
}

MeshRenderData::MeshRenderData(std::string shaderType) {
	m_shaderType = shaderType;
}

MeshRenderData::MeshRenderData(MeshData* data) : MeshRenderData::MeshRenderData(data, "Basic") {}

void MeshRenderData::setupVertexAttribPointer(std::string name, Shader* shader, int count, int offset, int stride) {
	GLint loc = shader->getAttributeLocation(name);

	if (loc >= 0) {
		glEnableVertexAttribArray(loc);
		glVertexAttribPointer(loc, count, GL_FLOAT, GL_FALSE, stride, (void*) offset);
	} else {
		logDebug(std::string("The shader type '") + m_shaderType + std::string("' does not support the attribute '") + name + std::string("'"));
	}
}

void MeshRenderData::setup(MeshData* data, bool generateVBOs) {
	//Check to see whether there are indices, and assign the appropriate number of vertices
	if (data->hasIndices()) {
		m_numVertices = data->getNumIndices();
		m_hasIndices = true;
	} else {
		m_numVertices = data->getNumPositions();
		m_hasIndices = false;
	}

	//Setup the VAO
	if (generateVBOs)
		glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	//The current stride being used
	GLuint currentStride = 0;

	//States whether the 'other' VBO is needed
	bool useOther = false;

	//The shader
	Shader* shader = Renderer::getShader(m_shaderType);

	//Check for any positions
	if (data->hasPositions() && data->separatePositions()) {
		//Setup the VBO
		if (generateVBOs)
			glGenBuffers(1, &m_position_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_position_vbo);
		glBufferData(GL_ARRAY_BUFFER, data->getNumPositions() * 3 * sizeof(data->getPositions()[0]), &data->getPositions().front(), m_positionsUsage);

		setupVertexAttribPointer("Position", shader, 3, 0, 0);
	} else if (data->hasPositions()) {
		currentStride += 3 * sizeof(data->getOthers()[0]);
		useOther = true;
	}

	//Check for any colours
	if (data->hasColours() && data->separateColours()) {
		//Setup the VBO
		if (generateVBOs)
			glGenBuffers(1, &m_colour_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_colour_vbo);
		glBufferData(GL_ARRAY_BUFFER, data->getNumColours() * 4 * sizeof(data->getColours()[0]), &data->getColours().front(), m_coloursUsage);

		setupVertexAttribPointer("Colour", shader, 4, 0, 0);
	} else if (data->hasColours()) {
		currentStride += 4 * sizeof(data->getOthers()[0]);
		useOther = true;
	}

	//Check for any texture coordinates
	if (data->hasTextureCoords() && data->separateTextureCoords()) {
		//Setup the VBO
		if (generateVBOs)
			glGenBuffers(1, &m_textureCoord_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_textureCoord_vbo);
		glBufferData(GL_ARRAY_BUFFER, data->getNumTextureCoords() * 2 * sizeof(data->getTextureCoords()[0]), &data->getTextureCoords().front(), m_textureCoordsUsage);

		setupVertexAttribPointer("TextureCoordinate", shader, 2, 0, 0);
	} else if (data->hasTextureCoords()) {
		currentStride += 2 * sizeof(data->getOthers()[0]);
		useOther = true;
	}

	//Check for any normals
	if (data->hasNormals() && data->separateNormals()) {
		//Setup the VBO
		if (generateVBOs)
			glGenBuffers(1, &m_normal_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_normal_vbo);
		glBufferData(GL_ARRAY_BUFFER, data->getNumNormals() * 3 * sizeof(data->getNormals()[0]), &data->getNormals().front(), m_normalsUsage);

		setupVertexAttribPointer("Normal", shader, 3, 0, 0);
	} else if (data->hasNormals()) {
		currentStride += 3 * sizeof(data->getOthers()[0]);
		useOther = true;
	}

	//Check for any tangents
	if (data->hasTangents() && data->separateTangents()) {
		//Setup the VBO
		if (generateVBOs)
			glGenBuffers(1, &m_tangent_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_tangent_vbo);
		glBufferData(GL_ARRAY_BUFFER, data->getNumTangents() * 3 * sizeof(data->getTangents()[0]), &data->getTangents().front(), m_normalsUsage);

		setupVertexAttribPointer("Tangent", shader, 3, 0, 0);
	} else if (data->hasTangents()) {
		currentStride += 3 * sizeof(data->getOthers()[0]);
		useOther = true;
	}

	//Check for any bitangents
	if (data->hasBitangents() && data->separateBitangents()) {
		//Setup the VBO
		if (generateVBOs)
			glGenBuffers(1, &m_tangent_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_tangent_vbo);
		glBufferData(GL_ARRAY_BUFFER, data->getNumBitangents() * 3 * sizeof(data->getBitangents()[0]), &data->getBitangents().front(), m_normalsUsage);

		setupVertexAttribPointer("Bitangent", shader, 3, 0, 0);
	} else if (data->hasBitangents()) {
		currentStride += 3 * sizeof(data->getOthers()[0]);
		useOther = true;
	}

	//Check to see whether the 'other' vbo is required
	if (useOther) {
		//The current offset needed
		GLuint currentOffset = 0;

		//Setup the VBO
		if (generateVBOs)
			glGenBuffers(1, &m_other_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_other_vbo);
		glBufferData(GL_ARRAY_BUFFER, data->getOthers().size() * sizeof(data->getOthers()[0]), &data->getOthers().front(), m_otherUsage);

		if (data->hasPositions() && ! data->separatePositions()) {
			m_positionsOffset = currentOffset;
			m_positionsStride = currentStride;

			currentOffset += 3 * sizeof(data->getOthers()[0]);

			setupVertexAttribPointer("Position", shader, 3, m_positionsOffset, m_positionsStride);
		}

		if (data->hasColours() && ! data->separateColours()) {
			m_coloursOffset = currentOffset;
			m_coloursStride = currentStride;

			currentOffset += 4 * sizeof(data->getOthers()[0]);

			setupVertexAttribPointer("Colour", shader, 4, m_coloursOffset, m_coloursStride);
		}

		if (data->hasTextureCoords() && ! data->separateTextureCoords()) {
			m_textureCoordsOffset = currentOffset;
			m_textureCoordsStride = currentStride;

			currentOffset += 2 * sizeof(data->getOthers()[0]);

			setupVertexAttribPointer("TextureCoordinate", shader, 2, m_textureCoordsOffset, m_textureCoordsStride);
		}

		if (data->hasNormals() && ! data->separateNormals()) {
			m_normalsOffset = currentOffset;
			m_normalsStride = currentStride;

			currentOffset += 3 * sizeof(data->getOthers()[0]);

			setupVertexAttribPointer("Normal", shader, 3, m_normalsOffset, m_normalsStride);
		}

		if (data->hasTangents() && ! data->separateTangents()) {
			m_tangentsOffset = currentOffset;
			m_tangentsStride = currentStride;

			currentOffset += 3 * sizeof(data->getOthers()[0]);

			setupVertexAttribPointer("Tangent", shader, 3, m_tangentsOffset, m_tangentsStride);
		}

		if (data->hasBitangents() && ! data->separateBitangents()) {
			m_bitangentsOffset = currentOffset;
			m_bitangentsStride = currentStride;

			currentOffset += 3 * sizeof(data->getOthers()[0]);

			setupVertexAttribPointer("Bitangent", shader, 3, m_bitangentsOffset, m_bitangentsStride);
		}
	}

	if (data->hasIndices()) {
		//Setup the VBO
		if (generateVBOs)
			glGenBuffers(1, &m_indices_vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indices_vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->getNumIndices() * sizeof(data->getIndices()[0]), &data->getIndices().front(), m_indicesUsage);
	}
	glBindVertexArray(0);
}

void MeshRenderData::render() {
	glBindVertexArray(m_vao);
	if (m_hasIndices) {
		glDrawElements(GL_TRIANGLES, m_numVertices, GL_UNSIGNED_INT, (void *) NULL);
	} else {
		glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
	}
	glBindVertexArray(0);
}

void MeshRenderData::updatePositions(MeshData* data) {
	if (data->hasIndices()) {
		m_numVertices = data->getIndices().size();
		m_hasIndices = true;
	} else {
		m_numVertices = data->getPositions().size();
		m_hasIndices = false;
	}
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_position_vbo);
	glBufferData(GL_ARRAY_BUFFER, data->getPositions().size() * sizeof(data->getPositions()[0]), &data->getPositions().front(), GL_STATIC_DRAW);

	GLint loc = Renderer::getShader(m_shaderType)->getAttributeLocation("Position");

	if (loc >= 0) {
		glEnableVertexAttribArray(loc);
		glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	} else
		logDebug(std::string("The shader type '") + m_shaderType + std::string("' does not support positions"));

	glBindVertexArray(0);

}

void MeshRenderData::updateIndices(MeshData* data) {
	m_numVertices = data->getIndices().size();
	m_hasIndices = true;

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indices_vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->getIndices().size() * sizeof(data->getIndices()[0]), &data->getIndices().front(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void MeshRenderData::updateColours(MeshData* data) {
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_colour_vbo);
	glBufferData(GL_ARRAY_BUFFER, data->getColours().size() * sizeof(data->getColours()[0]), &data->getColours().front(), GL_STATIC_DRAW);

	GLint loc = Renderer::getShader(m_shaderType)->getAttributeLocation("Colour");

	if (loc >= 0) {
		glEnableVertexAttribArray(loc);
		glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, 0);
	} else
		logDebug(std::string("The shader type '") + m_shaderType + std::string("' does not support colours"));

	glBindVertexArray(0);
}

void MeshRenderData::updateTextureCoords(MeshData* data) {
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_textureCoord_vbo);
	glBufferData(GL_ARRAY_BUFFER, data->getNumTextureCoords() * 2 * sizeof(data->getTextureCoords()[0]), &data->getTextureCoords().front(), m_textureCoordsUsage);

	setupVertexAttribPointer("TextureCoordinate", Renderer::getShader(m_shaderType), 2, 0, 0);

	glBindVertexArray(0);
}

MeshRenderData::~MeshRenderData() {
//	glDeleteBuffers(1, &m_position_vbo);
//	glDeleteBuffers(1, &m_colour_vbo);
//	glDeleteBuffers(1, &m_indices_vbo);
//	glDeleteVertexArrays(1, &m_vao);
}

/***************************************************************************************************/

/***************************************************************************************************
 * The MeshBuilder class provides various methods to make Mesh objects
 ***************************************************************************************************/

Mesh* MeshBuilder::createQuad(float width, float height, std::string shaderType, bool separatePositions, bool separateColours, bool separateTextureCoords) {
	MeshData* data = new MeshData(separatePositions, separateColours, separateTextureCoords);
	addQuadV(data, Vector2f(0, 0), Vector2f(width, height));
	addQuadI(data);
	return new Mesh(data, shaderType);
}

Mesh* MeshBuilder::createQuad(Vector2f topLeft, Vector2f bottomRight, std::string shaderType, bool separatePositions, bool separateColours, bool separateTextureCoords) {
	MeshData* data = new MeshData(separatePositions, separateColours, separateTextureCoords);
	addQuadV(data, topLeft, bottomRight);
	addQuadI(data);
	return new Mesh(data, shaderType);
}

Mesh* MeshBuilder::createQuad(float width, float height, Colour colour, std::string shaderType, bool separatePositions, bool separateColours, bool separateTextureCoords) {
	MeshData* data = new MeshData(separatePositions, separateColours, separateTextureCoords);
	addQuadV(data, Vector2f(0, 0), Vector2f(width, height));
	addQuadI(data);
	addQuadC(data, colour);
	return new Mesh(data, shaderType);
}
Mesh* MeshBuilder::createQuad(float width, float height, Colour colours[], int n, std::string shaderType, bool separatePositions, bool separateColours, bool separateTextureCoords) {
	MeshData* data = new MeshData(separatePositions, separateColours, separateTextureCoords);
	addQuadV(data, Vector2f(0, 0), Vector2f(width, height));
	addQuadI(data);
	addQuadC(data, colours, n);
	return new Mesh(data, shaderType);
}

Mesh* MeshBuilder::createQuad(float width, float height, Texture* texture, Colour colour, std::string shaderType, bool separatePositions, bool separateColours, bool separateTextureCoords) {
	MeshData* data = new MeshData(separatePositions, separateColours, separateTextureCoords);
	addQuadV(data, Vector2f(0, 0), Vector2f(width, height));
	addQuadI(data);
	addQuadC(data, colour);
	addQuadT(data, texture);
	return new Mesh(data, shaderType);
}
Mesh* MeshBuilder::createQuad(float width, float height, Texture* texture, Colour colours[], int n, std::string shaderType, bool separatePositions, bool separateColours, bool separateTextureCoords) {
	MeshData* data = new MeshData(separatePositions, separateColours, separateTextureCoords);
	addQuadV(data, Vector2f(0, 0), Vector2f(width, height));
	addQuadI(data);
	addQuadC(data, colours, n);
	addQuadT(data, texture);
	return new Mesh(data, shaderType);
}

void MeshBuilder::addQuadV(MeshData* data, float width, float height) {
	data->addPosition(Vector3f(0, 0, 0));
	data->addPosition(Vector3f(width, 0, 0));
	data->addPosition(Vector3f(width, height, 0));
	data->addPosition(Vector3f(0, height, 0));
}

void MeshBuilder::addQuadV(MeshData* data, Vector2f topLeft, Vector2f bottomRight) {
	data->addPosition(Vector3f(topLeft.getX(), topLeft.getY(), 0));
	data->addPosition(Vector3f(topLeft.getX(), bottomRight.getY(), 0));
	data->addPosition(Vector3f(bottomRight.getX(), bottomRight.getY(), 0));
	data->addPosition(Vector3f(bottomRight.getX(), topLeft.getY(), 0));
}

void MeshBuilder::addQuadI(MeshData* data) {
	data->addIndex(0);
	data->addIndex(1);
	data->addIndex(2);
	data->addIndex(3);
	data->addIndex(0);
	data->addIndex(2);
}

void MeshBuilder::addQuadC(MeshData* data, Colour colour) {
	data->addColour(colour);
	data->addColour(colour);
	data->addColour(colour);
	data->addColour(colour);
}

void MeshBuilder::addQuadC(MeshData* data, Colour colours[], int n) {
	int c = 0;
	for (int a = 0; a < 6; a++) {
		data->addColour(colours[c]);
		c++;
		if (c == n)
			c = 0;
	}
}

void MeshBuilder::addQuadT(MeshData* data, Texture* texture) {
//	data->addTextureCoord(Vector2f(texture->left, texture->top));
//	data->addTextureCoord(Vector2f(texture->right, texture->top));
//	data->addTextureCoord(Vector2f(texture->right, texture->bottom));
//	data->addTextureCoord(Vector2f(texture->left, texture->bottom));
	data->addTextureCoord(Vector2f(0, 1));
	data->addTextureCoord(Vector2f(0, 0));
	data->addTextureCoord(Vector2f(1, 0));
	data->addTextureCoord(Vector2f(1, 1));
}

//Start of 3D stuff

Mesh* MeshBuilder::createCube(float width, float height, float depth, std::string shaderType, bool separatePositions, bool separateColours, bool separateTextureCoords) {
	MeshData* data = new MeshData(separatePositions, separateColours, separateTextureCoords);
	addCubeV(data, width, height, depth);
	addCubeI(data);
	return new Mesh(data, shaderType);
}

Mesh* MeshBuilder::createCube(float width, float height, float depth, Colour colour, std::string shaderType, bool separatePositions, bool separateColours, bool separateTextureCoords) {
	MeshData* data = new MeshData(separatePositions, separateColours, separateTextureCoords);
	addCubeV(data, width, height, depth);
	addCubeI(data);
	addCubeC(data, colour);
	return new Mesh(data, shaderType);
}

Mesh* MeshBuilder::createCube(float width, float height, float depth, Colour colours[], int n, std::string shaderType, bool separatePositions, bool separateColours, bool separateTextureCoords) {
	MeshData* data = new MeshData(separatePositions, separateColours, separateTextureCoords);
	addCubeV(data, width, height, depth);
	addCubeI(data);
	addCubeC(data, colours, n);
	return new Mesh(data, shaderType);
}

Mesh* MeshBuilder::createCube(float width, float height, float depth, Texture* texture, Colour colour, std::string shaderType, bool separatePositions, bool separateColours, bool separateTextureCoords) {
	MeshData* data = new MeshData(separatePositions, separateColours, separateTextureCoords);
	addCubeV(data, width, height, depth);
	addCubeI(data);
	addCubeC(data, colour);
	addCubeT(data, texture);
	return new Mesh(data, shaderType);
}

Mesh* MeshBuilder::createCube(float width, float height, float depth, Texture* texture, Colour colours[], int n, std::string shaderType, bool separatePositions, bool separateColours, bool separateTextureCoords) {
	MeshData* data = new MeshData(separatePositions, separateColours, separateTextureCoords);
	addCubeV(data, width, height, depth);
	addCubeI(data);
	addCubeC(data, colours, n);
	addCubeT(data, texture);
	return new Mesh(data, shaderType);
}

Mesh* MeshBuilder::createCube(float width, float height, float depth, Texture* textures[], Colour colour, std::string shaderType, bool separatePositions, bool separateColours, bool separateTextureCoords) {
	MeshData* data = new MeshData(separatePositions, separateColours, separateTextureCoords);
	addCubeV(data, width, height, depth);
	addCubeI(data);
	addCubeC(data, colour);
	addCubeT(data, textures);
	return new Mesh(data, shaderType);
}

Mesh* MeshBuilder::createCube(float width, float height, float depth, Texture* textures[], Colour colours[], int n, std::string shaderType, bool separatePositions, bool separateColours, bool separateTextureCoords) {
	MeshData* data = new MeshData(separatePositions, separateColours, separateTextureCoords);
	addCubeV(data, width, height, depth);
	addCubeI(data);
	addCubeC(data, colours, n);
	addCubeT(data, textures);
	return new Mesh(data, shaderType);
}

void MeshBuilder::addCubeV(MeshData* data, float width, float height, float depth) {
	float w = width / 2;
	float h = height / 2;
	float d = depth / 2;
	//Front face
	data->addPosition(Vector3f(-w, h, d));
	data->addPosition(Vector3f(w, h, d));
	data->addPosition(Vector3f(w, -h, d));
	data->addPosition(Vector3f(-w, -h, d));

	//Left face
	data->addPosition(Vector3f(-w, -h, d));
	data->addPosition(Vector3f(-w, -h, -d));
	data->addPosition(Vector3f(-w, h, -d));
	data->addPosition(Vector3f(-w, h, d));

	//Back face
	data->addPosition(Vector3f(-w, h, -d));
	data->addPosition(Vector3f(w, h, -d));
	data->addPosition(Vector3f(w, -h, -d));
	data->addPosition(Vector3f(-w, -h, -d));

	//Bottom face
	data->addPosition(Vector3f(w, -h, -d));
	data->addPosition(Vector3f(w, -h, d));
	data->addPosition(Vector3f(-w, -h, d));
	data->addPosition(Vector3f(-w, -h, -d));

	//Right face
	data->addPosition(Vector3f(w, -h, -d));
	data->addPosition(Vector3f(w, -h, d));
	data->addPosition(Vector3f(w, h, d));
	data->addPosition(Vector3f(w, h, -d));

	//Top face
	data->addPosition(Vector3f(-w, h, -d));
	data->addPosition(Vector3f(-w, h, d));
	data->addPosition(Vector3f(w, h, d));
	data->addPosition(Vector3f(w, h, -d));
}

void MeshBuilder::addCubeI(MeshData* data) {
	//Front face
	//B-L triangle
	data->addIndex(0); data->addIndex(1); data->addIndex(2);
	//T-R
	data->addIndex(2); data->addIndex(3); data->addIndex(0);

	//Left face
	//B-L triangle
	data->addIndex(4); data->addIndex(5); data->addIndex(6);
	//T-R
	data->addIndex(6); data->addIndex(7); data->addIndex(4);

	//Back face
	//B-L triangle
	data->addIndex(8); data->addIndex(9); data->addIndex(10);
	//T-R
	data->addIndex(10); data->addIndex(11); data->addIndex(8);

	//Bottom face
	//B-L triangle
	data->addIndex(12); data->addIndex(13); data->addIndex(14);
	//T-R
	data->addIndex(14); data->addIndex(15); data->addIndex(12);

	//Right face
	//B-L triangle
	data->addIndex(16); data->addIndex(17); data->addIndex(18);
	//T-R
	data->addIndex(18); data->addIndex(19); data->addIndex(16);

	//Top face
	//B-L triangle
	data->addIndex(20); data->addIndex(21); data->addIndex(22);
	//T-R
	data->addIndex(22); data->addIndex(23); data->addIndex(20);
}

void MeshBuilder::addCubeC(MeshData* data, Colour colour) {
	for (int a = 0; a < 24; a++)
		data->addColour(colour);
}

void MeshBuilder::addCubeC(MeshData* data, Colour colours[], int n) {
	int c = 0;
	for (int a = 0; a < 24; a++) {
		data->addColour(colours[c]);
		c++;
		if (c == n)
			c = 0;
	}
}

void MeshBuilder::addCubeT(MeshData* data, Texture* texture) {
	data->addTextureCoord(Vector2f(texture->left, texture->top));
	data->addTextureCoord(Vector2f(texture->right, texture->top));
	data->addTextureCoord(Vector2f(texture->right, texture->bottom));
	data->addTextureCoord(Vector2f(texture->left, texture->bottom));

	data->addTextureCoord(Vector2f(texture->right, texture->bottom));
	data->addTextureCoord(Vector2f(texture->left, texture->bottom));
	data->addTextureCoord(Vector2f(texture->left, texture->top));
	data->addTextureCoord(Vector2f(texture->right, texture->top));

	data->addTextureCoord(Vector2f(texture->right, texture->bottom));
	data->addTextureCoord(Vector2f(texture->left, texture->bottom));
	data->addTextureCoord(Vector2f(texture->left, texture->top));
	data->addTextureCoord(Vector2f(texture->right, texture->top));

	data->addTextureCoord(Vector2f(texture->right, texture->bottom));
	data->addTextureCoord(Vector2f(texture->right, texture->top));
	data->addTextureCoord(Vector2f(texture->left, texture->top));
	data->addTextureCoord(Vector2f(texture->left, texture->bottom));

	data->addTextureCoord(Vector2f(texture->right, texture->bottom));
	data->addTextureCoord(Vector2f(texture->left, texture->bottom));
	data->addTextureCoord(Vector2f(texture->left, texture->top));
	data->addTextureCoord(Vector2f(texture->right, texture->top));

	data->addTextureCoord(Vector2f(texture->left, texture->top));
	data->addTextureCoord(Vector2f(texture->left, texture->bottom));
	data->addTextureCoord(Vector2f(texture->right, texture->bottom));
	data->addTextureCoord(Vector2f(texture->right, texture->top));
}

void MeshBuilder::addCubeT(MeshData* data, Texture* textures[]) {
	//Should include a check for the right number of textures
	data->addTextureCoord(Vector2f(textures[0]->left, textures[0]->top));
	data->addTextureCoord(Vector2f(textures[0]->right, textures[0]->top));
	data->addTextureCoord(Vector2f(textures[0]->right, textures[0]->bottom));
	data->addTextureCoord(Vector2f(textures[0]->left, textures[0]->bottom));

	data->addTextureCoord(Vector2f(textures[1]->right, textures[1]->bottom));
	data->addTextureCoord(Vector2f(textures[1]->left, textures[1]->bottom));
	data->addTextureCoord(Vector2f(textures[1]->left, textures[1]->top));
	data->addTextureCoord(Vector2f(textures[1]->right, textures[1]->top));

	data->addTextureCoord(Vector2f(textures[2]->right, textures[2]->bottom));
	data->addTextureCoord(Vector2f(textures[2]->left, textures[2]->bottom));
	data->addTextureCoord(Vector2f(textures[2]->left, textures[2]->top));
	data->addTextureCoord(Vector2f(textures[2]->right, textures[2]->top));

	data->addTextureCoord(Vector2f(textures[3]->right, textures[3]->bottom));
	data->addTextureCoord(Vector2f(textures[3]->right, textures[3]->top));
	data->addTextureCoord(Vector2f(textures[3]->left, textures[3]->top));
	data->addTextureCoord(Vector2f(textures[3]->left, textures[3]->bottom));

	data->addTextureCoord(Vector2f(textures[3]->right, textures[3]->bottom));
	data->addTextureCoord(Vector2f(textures[3]->left, textures[3]->bottom));
	data->addTextureCoord(Vector2f(textures[3]->left, textures[3]->top));
	data->addTextureCoord(Vector2f(textures[3]->right, textures[3]->top));

	data->addTextureCoord(Vector2f(textures[4]->left, textures[4]->top));
	data->addTextureCoord(Vector2f(textures[4]->left, textures[4]->bottom));
	data->addTextureCoord(Vector2f(textures[4]->right, textures[4]->bottom));
	data->addTextureCoord(Vector2f(textures[4]->right, textures[4]->top));
}

/***************************************************************************************************/
