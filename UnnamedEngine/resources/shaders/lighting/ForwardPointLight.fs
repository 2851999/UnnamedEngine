#include "ForwardLightingData.fs"

uniform PointLight pointLight;

void main() {
	FragColor = calculatePointLight(pointLight, frag_worldPosition, calculateNormal(), calculateShininess(), calculateColour());
}