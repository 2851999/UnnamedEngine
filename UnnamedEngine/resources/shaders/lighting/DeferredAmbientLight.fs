#include "DeferredLightingData.fs"

void main() {
	FragColor = ambientLight * texture2D(buffer_colour, frag_textureCoord);
}