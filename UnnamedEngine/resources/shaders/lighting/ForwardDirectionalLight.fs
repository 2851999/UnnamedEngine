#include "ForwardLightingData.fs"

uniform DirectionalLight directionalLight;

void main() {
	vec3 normal = frag_normal;
	
	if (material.useNormalMap > 0.5)
		normal = normalize(vec4((frag_tbnMatrix * ((2.0 * texture2D(material.normalMap, frag_textureCoord).xyz) - 1.0)), 0.0) * nMatrix).xyz;
		
	float s = 0.0;
	if (material.useSpecularTexture > 0.5)
		s = texture2D(material.specularTexture, frag_textureCoord).r * 255;
	else
		s = material.shininess;
	FragColor = calculateDirectionalLight(directionalLight, normal, s, material.diffuseColour * texture2D(material.diffuseTexture, frag_textureCoord));
}