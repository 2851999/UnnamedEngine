#version 140

#include "lighting/MaterialData.glsl"

/* The data passed on to the fragment shader */
in vec2 frag_textureCoord;

/* The fragment colour */
out vec4 FragColor;

/* The main method */
void main() {
	FragColor = material.diffuseColour * texture2D(material.diffuseTexture, frag_textureCoord);
}