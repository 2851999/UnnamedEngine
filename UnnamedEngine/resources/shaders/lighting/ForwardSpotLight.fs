#include "ForwardLightingData.fs"

uniform SpotLight spotLight;

void main() {
	FragColor = calculateSpotLight(spotLight, frag_worldPosition, calculateNormal(), calculateShininess(), calculateColour());
}