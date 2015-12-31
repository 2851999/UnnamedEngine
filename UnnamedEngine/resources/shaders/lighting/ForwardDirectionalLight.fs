#include "ForwardLightingData.fs"

uniform DirectionalLight directionalLight;

void main() {
	FragColor = calculateDirectionalLight(directionalLight, calculateNormal(), calculateShininess(), calculateColour());
}