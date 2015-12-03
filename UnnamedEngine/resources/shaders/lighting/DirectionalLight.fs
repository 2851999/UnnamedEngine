#include "LightingData.fs"

uniform DirectionalLight directionalLight;

void main() {
	FragColor = calculateDirectionalLight(directionalLight, frag_normal);
}