#include "Transformable.hpp"

Transformable::Transformable() {
	translation = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	rotationAngle = 0.0f;
	rotationAxis = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Transformable::rotate(float speed) {
	rotationAngle += speed * 3.14157f;

	/*if (rotationAngle > 2 * 3.14157f)
		rotationAngle = 0.0f;

	if (rotationAngle < 0.0f)
		rotationAngle = 0.0f;*/
}

glm::mat4 Transformable::makeModelMatrix() const {
	glm::mat4 t;
	t[0] = glm::vec4(1.0f, 0.0f, 0.0f, translation.x);
	t[1] = glm::vec4(0.0f, 1.0f, 0.0f, translation.y);
	t[2] = glm::vec4(0.0f, 0.0f, 1.0f, translation.z);
	t[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	glm::mat4 s;
	s[0] = glm::vec4(scale.x, 0.0f, 0.0f, 0.0f);
	s[1] = glm::vec4(0.0f, scale.y, 0.0f, 0.0f);
	s[2] = glm::vec4(0.0f, 0.0f, scale.z, 0.0f);
	s[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	glm::mat4 r;
	float a = rotationAngle * 3.14152f / 180.0f;
	r[0] = glm::vec4(cosf(a), 0.0f, -sinf(a), 0.0f);
	r[1] = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	r[2] = glm::vec4(sinf(a), 0.0f, cosf(a), 0.0f);
	r[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	return s * r * t;
}

glm::mat4 Transformable::makeModelInverseMatrix() const {
	glm::mat4 t;
	t[0] = glm::vec4(1.0f, 0.0f, 0.0f, -translation.x);
	t[1] = glm::vec4(0.0f, 1.0f, 0.0f, -translation.y);
	t[2] = glm::vec4(0.0f, 0.0f, 1.0f, -translation.z);
	t[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	glm::mat4 s;
	s[0] = glm::vec4(1 / scale.x, 0.0f, 0.0f, 0.0f);
	s[1] = glm::vec4(0.0f, 1 / scale.y, 0.0f, 0.0f);
	s[2] = glm::vec4(0.0f, 0.0f, 1 / scale.z, 0.0f);
	s[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		
	glm::mat4 r;
	float a = -rotationAngle * 3.14152f / 180.0f;
	r[0] = glm::vec4(cosf(a), 0.0f, -sinf(a), 0.0f);
	r[1] = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	r[2] = glm::vec4(sinf(a), 0.0f, cosf(a), 0.0f);
	r[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	return t * r * s;
}

void Transformable::setModelUniforms(const GpuProgram& program) const {
	program.setMat4("M", makeModelMatrix());
	program.setMat4("Minv", makeModelInverseMatrix());
}

void Transformable::resetTransormations() {
	translation = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	rotationAngle = 0.0f;
}