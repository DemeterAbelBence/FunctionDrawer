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

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec3 vertexColor;

uniform mat4 M;
uniform mat4 Minv;
uniform mat4 V;
uniform mat4 P;

uniform Material material;
uniform LightSource light;
uniform vec3 eye;

out vec3 radiance;

void main() {
	vec4 worldPosition = vec4(vertexPosition, 1) * M;
	vec4 worldNormal = Minv * vec4(vertexNormal, 0);
	vec4 finalPosition = worldPosition * V * P;
	gl_Position = finalPosition;

	vec3 lightPosition = vec3(vec4(light.position, 1) * V);

	vec3 V = normalize(eye - worldPosition.xyz);
	vec3 N = normalize(worldNormal.xyz);
	vec3 L = normalize(lightPosition - worldPosition.xyz);
	vec3 H = normalize(L + V);
			
	radiance = material.ambient * light.ambient;
	float lightCos = max(dot(N, L), 0);
	float viewCos = max(dot(N, H), 0);
	//radiance += (material.diffuse * lightCos +
		//material.specular * pow(viewCos, material.shininess)) * light.diffuse;

	radiance += material.diffuse * lightCos + material.specular * pow(viewCos, material.shininess) * light.diffuse;

	//radiance = vertexColor;
}