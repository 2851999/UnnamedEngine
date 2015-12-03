#version 140

#include "MaterialData.glsl"

struct BaseLight {
	vec3 colour;
	float intensity;
};

struct Attenuation {
	float constant;
	float linear;
	float exponent;
};

struct DirectionalLight {
	BaseLight base;
	vec3 direction;
};

struct PointLight {
	BaseLight base;
	Attenuation attenuation;
	vec3 position;
	float range;
};

struct SpotLight {
	PointLight pointLight;
	vec3 direction;
	float cutoff;
};

uniform vec4 ambientLight;
uniform float specularIntensity;
uniform vec3 eyePosition;

in vec3 frag_vertex;
in vec2 frag_textureCoord;
in vec3 frag_normal;

in vec3 frag_worldPosition;

/* The fragment colour */
out vec4 FragColor;

vec4 calculateLight(BaseLight base, vec3 direction, vec3 normal) {
	float diffuseFactor = max(dot(normal, -direction), 0.0);
	vec4 diffuseColour = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 specularColour = vec4(0.0, 0.0, 0.0, 0.0);
	if (diffuseFactor > 0.0) {
		diffuseColour = vec4(base.colour * base.intensity * diffuseFactor, 1.0);
		
		vec3 reflectDir = reflect(-direction, normal);
		float specAngle = max(dot(reflectDir, normalize(eyePosition)), 0.0);
		
		if (specAngle > 0.0) {
			float specularFactor = pow(specAngle, material.shininess);
			specularColour = vec4(base.colour, 1.0) * specularIntensity * specularFactor;
		}
	}
	return (diffuseColour + specularColour) * material.diffuseColour * texture2D(material.diffuseTexture, frag_textureCoord);
}

vec4 calculateDirectionalLight(DirectionalLight directionalLight, vec3 normal) {
	return calculateLight(directionalLight.base, -directionalLight.direction, normal);
}

vec4 calculatePointLight(PointLight pointLight, vec3 normal) {
	vec3 lightDirection = frag_worldPosition - pointLight.position;
	float distanceToLight = length(lightDirection);
	
	if (distanceToLight > pointLight.range)
		return vec4(0.0, 0.0, 0.0, 1.0);
	
	lightDirection = normalize(lightDirection);
	
	vec4 colour = calculateLight(pointLight.base, lightDirection, normal);
	
	float attenuation = pointLight.attenuation.constant +
						pointLight.attenuation.linear * distanceToLight +
						pointLight.attenuation.exponent * distanceToLight * distanceToLight + 0.00001;
						//Make sure /0 never occurs, as glsl sometimes will execute both code paths of an if statement at the same time
	return vec4(colour.xyz / attenuation, colour.w);
}

vec4 calculateSpotLight(SpotLight spotLight, vec3 normal) {
	vec3 lightDirection = normalize(frag_worldPosition - spotLight.pointLight.position);
	float spotFactor = dot(lightDirection, spotLight.direction);
	vec4 colour = vec4(0.0, 0.0, 0.0, 1.0);
	
	if (spotFactor > spotLight.cutoff) {
		colour = calculatePointLight(spotLight.pointLight, normal);
		colour = vec4(colour.xyz *
				(1.0 - (1.0 - spotFactor) / (1.0 - spotLight.cutoff)), colour.w); //Give it a softer edge - could have /0
	}
	return colour;
}

