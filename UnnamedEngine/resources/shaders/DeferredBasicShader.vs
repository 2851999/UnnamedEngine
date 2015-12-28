#version 140

/* The model view projection matrix */
uniform mat4 mvpMatrix;

/* The data being passed in */
in vec3 position;
in vec2 textureCoord;

/* The data passed on to the fragment shader */
out vec2 frag_textureCoord;

/* The main method */
void main() {
	frag_textureCoord = textureCoord;
	
	gl_Position = mvpMatrix * vec4(position, 1.0);
}