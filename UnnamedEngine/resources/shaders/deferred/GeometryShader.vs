#version 140

uniform mat4 mMatrix;
uniform mat3 nMatrix;
uniform mat4 mvpMatrix;

in vec3 position;
in vec2 textureCoord;
in vec3 normal;
in vec3 tangent;
in vec3 bitangent;

out vec3 frag_vertex;
out vec2 frag_textureCoord;
out vec3 frag_normal;
out vec3 frag_worldPosition;

out mat3 frag_tbnMatrix;

void main() {
	frag_vertex = vec3(mvpMatrix * vec4(position, 1.0));
	frag_textureCoord = textureCoord;
	frag_normal = normalize(normal * nMatrix).xyz;
	frag_worldPosition = (vec4(position, 1.0) * mMatrix).xyz; //Done for point lights which rely on this being in the same space as the light position
	
	gl_Position = mvpMatrix * vec4(position, 1.0);
	
	vec3 n = normalize((vec4(normal, 0.0)).xyz);
	vec3 t = normalize((vec4(tangent, 0.0)).xyz);
	vec3 b = normalize((vec4(bitangent, 0.0)).xyz);
	
	frag_tbnMatrix = mat3(t, b, n);
}