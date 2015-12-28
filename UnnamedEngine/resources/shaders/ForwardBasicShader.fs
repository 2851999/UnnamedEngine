#version 140

/* The texture */
uniform sampler2D tex;

/* The data passed on to the fragment shader */
in vec4 frag_colour;
in vec2 frag_textureCoord;

/* The fragment colour */
out vec4 FragColor;

/* The main method */
void main() {
	FragColor = frag_colour * texture2D(tex, frag_textureCoord);
}