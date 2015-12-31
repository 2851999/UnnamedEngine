#include "DeferredLightingData.fs"

uniform PointLight pointLight;

void main() {
	FragColor = calculatePointLight(pointLight, texture2D(buffer_worldPosition, frag_textureCoord).rgb, calculateNormal(), calculateShininess(), calculateColour());
}