#version 140

/* The model view projection matrix */
uniform mat4 mvpMatrix;

/* The data being passed in */
in vec3 position;

/* The data being passed to the fragment shader */
out vec3 frag_textureCoord;

/* The main method */
void main() {
	frag_textureCoord = position;
	
	gl_Position = mvpMatrix * vec4(position, 1.0);
}