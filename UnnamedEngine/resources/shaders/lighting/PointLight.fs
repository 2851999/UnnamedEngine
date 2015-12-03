#include "LightingData.fs"

uniform PointLight pointLight;

void main() {
	FragColor = calculatePointLight(pointLight, frag_normal);
}