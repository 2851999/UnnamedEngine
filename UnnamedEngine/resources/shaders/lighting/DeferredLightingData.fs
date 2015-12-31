#include "LightingData.fs"

/* The textures */
uniform sampler2D buffer_worldPosition;
uniform sampler2D buffer_colour;
uniform sampler2D buffer_normal;
uniform sampler2D buffer_shininess;
uniform sampler2D buffer_depth;

/* The data passed on to the fragment shader */
in vec2 frag_textureCoord;

/* The fragment colour */
out vec4 FragColor;

float calculateShininess() {
	return texture2D(buffer_shininess, frag_textureCoord).r * 255;
}

vec3 calculateNormal() {
	return texture2D(buffer_normal, frag_textureCoord).rgb;
}

vec4 calculateColour() {
	return texture2D(buffer_colour, frag_textureCoord);
}