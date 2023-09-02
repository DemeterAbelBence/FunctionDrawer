#version 330 core

precision highp float;

layout(location = 0) in vec3 vertexPosition;

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
uniform vec3 eye;

uniform mat4 M;
uniform mat4 Minv;
uniform mat4 V;
uniform mat4 P;

out vec3 radiance;

void main() {
	vec4 worldPosition = vec4(vertexPosition, 1) * M;
	vec4 finalPosition = worldPosition * V * P;
	gl_Position = finalPosition;

	float l = length(eye - vec3(worldPosition));
	radiance = log(l);
}