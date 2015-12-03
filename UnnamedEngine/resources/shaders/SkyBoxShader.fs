#version 140

/* The texture */
uniform samplerCube tex;

/* The data being passed in */
in vec3 frag_textureCoord;

/* The data being passed out */
out vec4 FragColor;

/* The main method */
void main() {
	FragColor = texture(tex, frag_textureCoord);
}