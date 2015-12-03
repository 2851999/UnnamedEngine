#include "LightingData.fs"

uniform SpotLight spotLight;

void main() {
	FragColor = calculateSpotLight(spotLight, frag_normal);
}