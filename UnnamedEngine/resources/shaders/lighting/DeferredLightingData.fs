#include "LightingData.fs"

/* The textures */
uniform sampler2D buffer_worldPosition;
uniform sampler2D buffer_colour;
uniform sampler2D buffer_normal;
uniform sampler2D buffer_shininess;

/* The data passed on to the fragment shader */
in vec2 frag_textureCoord;

/* The fragment colour */
out vec4 FragColor;