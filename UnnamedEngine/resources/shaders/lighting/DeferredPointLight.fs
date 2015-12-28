#include "DeferredLightingData.fs"

uniform PointLight pointLight;

void main() {
	FragColor = calculatePointLight(pointLight, texture2D(buffer_worldPosition, frag_textureCoord).rgb, texture2D(buffer_normal, frag_textureCoord).rgb, texture2D(buffer_shininess, frag_textureCoord).r * 255.0, texture2D(buffer_colour, frag_textureCoord));
}