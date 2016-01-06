#version 140
#include "MaterialData.glsl"

uniform mat3 nMatrix;

in vec3 frag_vertex;
in vec2 frag_textureCoord;
in vec3 frag_normal;
in vec3 frag_worldPosition;

in mat3 frag_tbnMatrix;

out vec4 FragWorldPosition;
out vec4 FragColour;
out vec4 FragNormal;
out vec4 FragShininess;

void main() {
	FragWorldPosition = vec4(frag_worldPosition, 1.0);
	FragColour = (material.diffuseColour * texture2D(material.diffuseTexture, frag_textureCoord));
	FragNormal = vec4(frag_normal, 1.0);
	if (material.useNormalMap > 0.5)
		FragNormal = vec4(normalize((frag_tbnMatrix * ((2.0 * texture2D(material.normalMap, frag_textureCoord).xyz) - 1.0)) * nMatrix).xyz, 1.0);
		//FragNormal = vec4(normalize(vec4(frag_tbnMatrix * 2.0 * texture2D(material.normalMap, frag_textureCoord).rgb - 0.5, 0.0)).xyz, 1.0);
	//FragNormal = normalize(FragNormal);
	
	float s = 0.0;
	if (material.useShininessTexture > 0.5)
		s = texture2D(material.shininessTexture, frag_textureCoord).r;
	else
		s = material.shininess / 255.0;
	FragShininess = vec4(s, s, s, 1.0);
}