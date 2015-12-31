#include "DeferredLightingData.fs"

uniform SpotLight spotLight;

void main() {
	FragColor = calculateSpotLight(spotLight, texture2D(buffer_worldPosition, frag_textureCoord).rgb, calculateNormal(), calculateShininess(), calculateColour());
}