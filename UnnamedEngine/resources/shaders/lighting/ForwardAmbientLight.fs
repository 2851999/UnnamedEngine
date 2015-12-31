#include "ForwardLightingData.fs"

void main() {
	FragColor = ambientLight * calculateColour();
}