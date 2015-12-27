#version 140

uniform mat4 nMatrix;
uniform mat4 mvpMatrix;

in vec3 position;
in vec2 textureCoord;
in vec3 normal;

out vec3 frag_vertex;
out vec2 frag_textureCoord;
out vec3 frag_normal;
out vec3 frag_worldPosition;

void main() {
	frag_vertex = vec3(mvpMatrix * vec4(position, 1.0));
	frag_textureCoord = textureCoord;
	frag_normal = normalize(vec4(normal, 0.0) * nMatrix).xyz;
	frag_worldPosition = position; //Done for point lights which rely on this being in the same space as the light position
	
	gl_Position = mvpMatrix * vec4(position, 1.0);
}