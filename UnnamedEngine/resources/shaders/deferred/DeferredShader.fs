#version 140
#include "MaterialData.glsl"

in vec3 frag_vertex;
in vec2 frag_textureCoord;
in vec3 frag_normal;
in vec3 frag_worldPosition;

out vec4 FragWorldPosition;
out vec4 FragColour;
out vec4 FragNormal;
out vec4 FragShininess;

void main() {
	FragWorldPosition = vec4(frag_worldPosition, 1.0);
	FragColour = (material.diffuseColour * texture2D(material.diffuseTexture, frag_textureCoord));
	FragNormal = vec4(frag_normal, 1.0);
	float s = material.shininess / 255.0;
	FragShininess = vec4(s, s, s, 1.0);
}