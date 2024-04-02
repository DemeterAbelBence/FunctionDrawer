#version 330 core

precision highp float;

struct LightSource {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
};

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;
uniform LightSource light;

in vec3 wV;
in vec3 wN;
in vec3 wL;

out vec4 fragmentColor;

void main() {
	vec3 wH = normalize(wL + wV);
	vec3 radiance;

	radiance = material.ambient * light.ambient;
	float lightCos = max(dot(wN, wL), 0);
	float viewCos = max(dot(wN, wH), 0);
	radiance += (material.diffuse * lightCos + 
		material.specular * pow(viewCos, material.shininess) * light.diffuse);

	fragmentColor = vec4(radiance, 1);
}