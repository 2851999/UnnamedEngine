#include "LightingData.fs"

void main() {
	FragColor = ambientLight * (material.diffuseColour * texture2D(material.diffuseTexture, frag_textureCoord));
}