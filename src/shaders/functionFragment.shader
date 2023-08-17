#version 330 core

precision highp float;

in vec3 radiance;
out vec4 fragmentColor;

void main() {
	float fadingFactor = 0;
	if (gl_FragCoord.z > 0) {
		fadingFactor = gl_FragCoord.z;
	}
	vec3 r = radiance * fadingFactor;
	fragmentColor = vec4(r, 1);
}