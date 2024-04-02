#version 330 core

precision highp float;

layout(location = 0) in vec3 vertexPosition;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform vec3 eye;

out vec3 color;

void main() {
	vec4 modelPosition = vec4(vertexPosition, 1) * M;
	vec4 finalPosition = modelPosition * V * P;

	gl_Position = finalPosition;


	float colorFactor = 1 / (modelPosition.z * modelPosition.z);
	color = vec3(0.2f + colorFactor, 0.2f + colorFactor, 0.2f + colorFactor);

}