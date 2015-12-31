#include "DeferredLightingData.fs"

uniform DirectionalLight directionalLight;
 
uniform mat4 projection;

void main() {

	

	FragColor = calculateDirectionalLight(directionalLight, calculateNormal(), calculateShininess(), calculateColour());
}