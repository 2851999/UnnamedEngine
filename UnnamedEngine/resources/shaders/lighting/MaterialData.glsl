/* The material data */
struct Material {
	sampler2D diffuseTexture;
	
	vec4 ambientColour;
	vec4 diffuseColour;
	vec4 specularColour;
	
	float shininess;
};

/* The material */
uniform Material material;
