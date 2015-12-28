/* The material data */
struct Material {
	sampler2D diffuseTexture;
	sampler2D specularTexture;
	sampler2D normalMap;
	
	vec4 ambientColour;
	vec4 diffuseColour;
	vec4 specularColour;
	
	float useSpecularTexture;
	float useNormalMap;
	
	float shininess;
};

/* The material */
uniform Material material;