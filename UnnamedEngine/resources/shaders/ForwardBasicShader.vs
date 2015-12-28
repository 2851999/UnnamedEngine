#version 140

/* The model view projection matrix */
uniform mat4 mvpMatrix;

/* The data being passed in */
in vec3 position;
in vec4 colour;
in vec2 textureCoord;

/* The data passed on to the fragment shader */
out vec4 frag_colour;
out vec2 frag_textureCoord;

/* The main method */
void main() {
	frag_colour = colour;
	frag_textureCoord = textureCoord;
	
	gl_Position = mvpMatrix * vec4(position, 1.0);
}