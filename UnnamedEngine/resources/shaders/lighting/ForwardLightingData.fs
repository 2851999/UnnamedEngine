#include "LightingData.fs"
#include "MaterialData.glsl"

uniform mat3 nMatrix;

in vec3 frag_vertex;
in vec2 frag_textureCoord;
in vec3 frag_normal;
in vec3 frag_worldPosition;

in mat3 frag_tbnMatrix;

/* The fragment colour */
out vec4 FragColor;

float calculateShininess() {
	if (material.useShininessTexture > 0.5)
		return texture2D(material.shininessTexture, frag_textureCoord).r * 255;
	else
		return material.shininess;
}

vec3 calculateNormal() {
	if (material.useNormalMap > 0.5)
		return normalize((frag_tbnMatrix * ((2.0 * texture2D(material.normalMap, frag_textureCoord).xyz) - 1.0)) * nMatrix).xyz;
	else
		return frag_normal;
}

vec4 calculateColour() {
	return material.diffuseColour * texture2D(material.diffuseTexture, frag_textureCoord);
}