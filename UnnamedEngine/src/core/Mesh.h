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

#ifndef CORE_MESH_H_
#define CORE_MESH_H_

#include<iostream>
#include<string>
#include<vector>

#include "../utils/MathUtils.h"
#include "render/Material.h"
#include "Vector.h"
#include "Texture.h"

/***************************************************************************************************
 * The Mesh class stores data that can be used to render a mesh
 ***************************************************************************************************/

class MeshData {
private:
	/* The data */
	std::vector<float> m_positions;
	std::vector<float> m_colours;
	std::vector<float> m_normals;
	std::vector<float> m_textureCoords;
	std::vector<float> m_other;
	std::vector<unsigned int> m_indices;

	/* The values that determine whether certain data should be kept in separate VBO's (True by default) */
	bool m_separatePositions = true;
	bool m_separateColours   = true;
	bool m_separateTextureCoords = true;
	bool m_separateNormals   = true;

	/* The number of each value that is stored */
	unsigned int m_numPositions = 0;
	unsigned int m_numColours = 0;
	unsigned int m_numTextureCoordinates = 0;
	unsigned int m_numNormals = 0;
	unsigned int m_numIndices = 0;
public:
	MeshData() {
		m_positions     = std::vector<float>();
		m_colours       = std::vector<float>();
		m_normals       = std::vector<float>();
		m_textureCoords = std::vector<float>();
		m_other         = std::vector<float>();
		m_indices       = std::vector<unsigned int>();
	}

	MeshData(bool separatePositions, bool separateColours, bool separateTextureCoords, bool separateNormals) : MeshData() {
		m_separatePositions = separatePositions;
		m_separateColours = separateColours;
		m_separateTextureCoords = separateTextureCoords;
		m_separateNormals = separateNormals;
	}

	inline void addPosition(Vector3f position) {
		if (m_separatePositions) {
			m_positions.push_back(position.getX());
			m_positions.push_back(position.getY());
			m_positions.push_back(position.getZ());
		} else {
			m_other.push_back(position.getX());
			m_other.push_back(position.getY());
			m_other.push_back(position.getZ());
		}
		m_numPositions++;
	}
	inline void addColour(Vector4f colour) {
		if (m_separateColours) {
			m_colours.push_back(colour.getX());
			m_colours.push_back(colour.getY());
			m_colours.push_back(colour.getZ());
			m_colours.push_back(colour.getW());
		} else {
			m_other.push_back(colour.getX());
			m_other.push_back(colour.getY());
			m_other.push_back(colour.getZ());
			m_other.push_back(colour.getW());
		}
		m_numColours++;
	}
	inline void addNormal(Vector3f normal) {
		if (m_separateNormals) {
			m_normals.push_back(normal.getX());
			m_normals.push_back(normal.getY());
			m_normals.push_back(normal.getZ());
		} else {
			m_other.push_back(normal.getX());
			m_other.push_back(normal.getY());
			m_other.push_back(normal.getZ());
		}
		m_numNormals++;
	}
	inline void addTextureCoord(Vector2f textureCoord) {
		if (m_separateTextureCoords) {
			m_textureCoords.push_back(textureCoord.getX());
			m_textureCoords.push_back(textureCoord.getY());
		} else {
			m_other.push_back(textureCoord.getX());
			m_other.push_back(textureCoord.getY());
		}
		m_numTextureCoordinates++;
	}
	inline void addIndex(unsigned int index)           { m_indices.push_back(index); m_numIndices++; }

	inline std::vector<float> getPositions()        { return m_positions;                      }
	inline std::vector<float> getColours()          { return m_colours;                        }
	inline std::vector<float> getNormals()          { return m_normals;                        }
	inline std::vector<float> getTextureCoords()    { return m_textureCoords;                  }
	inline std::vector<float> getOthers()   		{ return m_other;                        }
	inline std::vector<unsigned int> getIndices()   { return m_indices;                        }

	inline bool separatePositions() { return m_separatePositions; }
	inline bool separateColours() { return m_separateColours; }
	inline bool separateTextureCoords() { return m_separateTextureCoords; }
	inline bool separateNormals() { return m_separateNormals; }

	inline void clearPositions() { m_positions.clear(); }
	inline void clearColours() { m_colours.clear(); }
	inline void clearTextureCoords() { m_textureCoords.clear(); }
	inline void clearIndices() { m_indices.clear(); }

	inline bool hasPositions()     { return m_numPositions > 0; }
	inline bool hasColours()       { return m_numColours > 0; }
	inline bool hasTextureCoords() { return m_numTextureCoordinates > 0; }
	inline bool hasNormals()       { return m_numNormals > 0; }
	inline bool hasIndices()       { return m_numIndices > 0; }

	inline unsigned int getNumPositions() { return m_numPositions; }
	inline unsigned int getNumColours() { return m_numColours; }
	inline unsigned int getNumTextureCoords() { return m_numTextureCoordinates; }
	inline unsigned int getNumNormals() { return m_numNormals; }
	inline unsigned int getNumIndices() { return m_numIndices; }
};

class MeshRenderData {
private:
	/* The vertex array object */
	GLuint m_vao              = -1;

	/* The vbo's */
	GLuint m_position_vbo     = -1;
	GLuint m_colour_vbo       = -1;
	GLuint m_normal_vbo       = -1;
	GLuint m_textureCoord_vbo = -1;
	GLuint m_indices_vbo      = -1;
	GLuint m_other_vbo        = -1;

	/* The offset and strides */
	int m_positionsOffset = 0;
	int m_positionsStride = 0;
	int m_coloursOffset   = 0;
	int m_coloursStride   = 0;
	int m_textureCoordsOffset = 0;
	int m_textureCoordsStride = 0;
	int m_normalsOffset   = 0;
	int m_normalsStride   = 0;

	/* The usage values */
	int m_positionsUsage = GL_STATIC_DRAW;
	int m_coloursUsage  = GL_STATIC_DRAW;
	int m_textureCoordsUsage = GL_STATIC_DRAW;
	int m_normalsUsage  = GL_STATIC_DRAW;
	int m_otherUsage    = GL_STATIC_DRAW;
	int m_indicesUsage  = GL_STATIC_DRAW;

	int m_numVertices         = 0;
	bool m_hasIndices         = false;

	Material* m_material = NULL;
	std::string m_shaderType = "Basic";

private:
	void setupVertexAttribPointer(std::string name, Shader* shader, int count, int offset, int stride);
public:
	MeshRenderData() { }
	MeshRenderData(MeshData* data);
	MeshRenderData(std::string shaderType);
	MeshRenderData(MeshData* data, std::string shaderType);
	virtual ~MeshRenderData();

	void setup(MeshData* data, bool generateVBOs);

	void render();

	void updateVertices(MeshData* data);
	void updateColours(MeshData* data);
	void updateTextureCoords(MeshData* data);
	void updateIndices(MeshData* data);

	inline void setMaterial(Material* material) { m_material = material; }
	inline void setShaderType(std::string shaderType) { m_shaderType = shaderType; }
	inline Material* getMaterial() { return m_material; }
	inline std::string getShaderType() { return m_shaderType; }
	inline bool hasMaterial() { return m_material != NULL; }
	inline int getNumVertices() { return m_numVertices; }
};

class Mesh {
private:
	MeshData* m_data;
	MeshRenderData* m_renderData;
	Texture* m_texture;
public:
	Mesh() { m_data = NULL; m_renderData = NULL; m_texture = NULL; }
	Mesh(MeshData* data) { m_data = data; m_renderData = new MeshRenderData(m_data); m_texture = NULL; }
	Mesh(MeshData* data, std::string shaderType) { m_data = data; m_renderData = new MeshRenderData(m_data, shaderType); m_texture = NULL; }
	virtual ~Mesh() { }

	inline void render() { m_renderData->render(); }
	inline void setTexture(Texture* texture) { m_texture = texture; }
	inline Texture* getTexture() { return m_texture; }
	inline bool hasTexture() { return m_texture != NULL; }
	inline MeshData* getData() { return m_data; }
	inline MeshRenderData* getRenderData() { return m_renderData; }
	inline void updateVertices() { m_renderData->updateVertices(m_data); }
	inline void updateColours() { m_renderData->updateColours(m_data); }
	inline void updateTextureCoords() { m_renderData->updateTextureCoords(m_data); }
	inline void updateIndices() { m_renderData->updateIndices(m_data); }
};

/***************************************************************************************************/

/***************************************************************************************************
 * The MeshBuilder class provides various methods to make Mesh objects
 ***************************************************************************************************/

class MeshBuilder {
public:
	//2D stuff
	static inline Mesh* createQuad(Vector2f topLeft, Vector2f bottomRight) { return createQuad(topLeft, bottomRight, "Basic"); }
	static inline Mesh* createQuad(float width, float height) { return createQuad(width, height, "Basic"); }
	static inline Mesh* createQuad(float width, float height, Colour colour) { return createQuad(width, height, colour, "Basic"); }
	static inline Mesh* createQuad(float width, float height, Colour colours[], int n) { return createQuad(width, height, colours, n, "Basic"); }
	static inline Mesh* createQuad(float width, float height, Texture* texture, Colour colour) { return createQuad(width, height, texture, colour, "Basic"); }
	static inline Mesh* createQuad(float width, float height, Texture* texture, Colour colours[], int n) { return createQuad(width, height, texture, colours, n, "Basic"); }

	static Mesh* createQuad(Vector2f topLeft, Vector2f bottomRight, std::string shaderType);
	static Mesh* createQuad(float width, float height, std::string shaderType);
	static Mesh* createQuad(float width, float height, Colour colour, std::string shaderType);
	static Mesh* createQuad(float width, float height, Colour colours[], int n, std::string shaderType);
	static Mesh* createQuad(float width, float height, Texture* texture, Colour colour, std::string shaderType);
	static Mesh* createQuad(float width, float height, Texture* texture, Colour colours[], int n, std::string shaderType);

	static void addQuadV(MeshData* data, float width, float height);
	static void addQuadV(MeshData* data, Vector2f topLeft, Vector2f bottomRight);
	static void addQuadI(MeshData* data);
	static void addQuadC(MeshData* data, Colour colour);
	static void addQuadC(MeshData* data, Colour colours[], int n);
	static void addQuadT(MeshData* data, Texture* texture);

	//3D stuff
	static inline Mesh* createCube(float width, float height, float depth) { return createCube(width, height, depth, "Basic"); }
	static inline Mesh* createCube(float width, float height, float depth, Colour colour) { return createCube(width, height, depth, colour, "Basic"); }
	static inline Mesh* createCube(float width, float height, float depth, Colour colours[], int n) { return createCube(width, height, depth, colours, n, "Basic"); }
	static inline Mesh* createCube(float width, float height, float depth, Texture* texture, Colour colour) { return createCube(width, height, depth, texture, colour, "Basic"); }
	static inline Mesh* createCube(float width, float height, float depth, Texture* texture, Colour colours[], int n) { return createCube(width, height, depth, texture, colours, n, "Basic"); }
	static inline Mesh* createCube(float width, float height, float depth, Texture* textures[], Colour colour) { return createCube(width, height, depth, textures, colour, "Basic"); }
	static inline Mesh* createCube(float width, float height, float depth, Texture* textures[], Colour colours[], int n) { return createCube(width, height, depth, textures, colours, n, "Basic"); }

	static Mesh* createCube(float width, float height, float depth, std::string shaderType);
	static Mesh* createCube(float width, float height, float depth, Colour colour, std::string shaderType);
	static Mesh* createCube(float width, float height, float depth, Colour colours[], int n, std::string shaderType);
	static Mesh* createCube(float width, float height, float depth, Texture* texture, Colour colour, std::string shaderType);
	static Mesh* createCube(float width, float height, float depth, Texture* texture, Colour colours[], int n, std::string shaderType);
	static Mesh* createCube(float width, float height, float depth, Texture* textures[], Colour colour, std::string shaderType);
	static Mesh* createCube(float width, float height, float depth, Texture* textures[], Colour colours[], int n, std::string shaderType);

	static void addCubeV(MeshData* data, float width, float height, float depth);
	static void addCubeI(MeshData* data);
	static void addCubeC(MeshData* data, Colour colour);
	static void addCubeC(MeshData* data, Colour colours[], int n);
	static void addCubeT(MeshData* data, Texture* texture);
	static void addCubeT(MeshData* data, Texture* textures[]);
};

/***************************************************************************************************/

#endif
