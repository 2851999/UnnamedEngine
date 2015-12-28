#include "DeferredLightingData.fs"

uniform SpotLight spotLight;

void main() {
	FragColor = calculateSpotLight(spotLight, texture2D(buffer_worldPosition, frag_textureCoord).rgb, texture2D(buffer_normal, frag_textureCoord).rgb, texture2D(buffer_shininess, frag_textureCoord).r * 255.0, texture2D(buffer_colour, frag_textureCoord));
}