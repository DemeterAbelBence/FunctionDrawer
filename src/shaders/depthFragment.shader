#version 330 core

precision highp float;

out vec4 fragmentColor;
in vec3 radiance;

void main() {
	fragmentColor = vec4(radiance, 1);
}