#version 330 core

precision highp float;		

struct LightSource {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
};

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec3 vertexColor;

uniform mat4 M;
uniform mat4 Minv;
uniform mat4 V;
uniform mat4 P;

uniform LightSource light;
uniform vec3 eye;

out vec3 wV;
out vec3 wN;
out vec3 wL;

void main() {
	vec4 worldPosition = vec4(vertexPosition, 1) * M;
	vec4 worldNormal = Minv * vec4(vertexNormal, 0);
	vec4 finalPosition = worldPosition * V * P;
	gl_Position = finalPosition;

	vec3 lightPosition = vec3(vec4(light.position, 1) * V);

	wV = normalize(eye - worldPosition.xyz);
	wN = normalize(worldNormal.xyz);
	wL = normalize(lightPosition - worldPosition.xyz);		
}