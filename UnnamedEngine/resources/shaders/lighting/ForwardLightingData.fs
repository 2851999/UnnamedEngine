#include "LightingData.fs"
#include "MaterialData.glsl"

uniform mat4 nMatrix;

in vec3 frag_vertex;
in vec2 frag_textureCoord;
in vec3 frag_normal;
in vec3 frag_worldPosition;

in mat3 frag_tbnMatrix;

/* The fragment colour */
out vec4 FragColor;