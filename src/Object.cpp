#include "Object.hpp"

Object::Object() {
	translation = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	rotationAngle = 0.0f;
	rotationAxis = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Object::rotate(float degrees) {
	rotationAngle += degrees * 3.14157 / 180;

	if (rotationAngle > 360.0f)
		rotationAngle = 0.0f;

	if (rotationAngle < -360.0f)
		rotationAngle = 0.0f;
}

glm::mat4 Object::makeModelMatrix() const {
	glm::mat4 t = glm::translate(translation);
	glm::mat4 s = glm::scale(scale);
	//glm::mat4 r = glm::rotation(rotationAngle, rotationAxis);

	glm::mat4 r;
	r[0] = glm::vec4(cosf(rotationAngle), 0.0f, -sinf(rotationAngle), 0.0f);
	r[1] = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	r[2] = glm::vec4(sinf(rotationAngle), 0.0f, cosf(rotationAngle), 0.0f);
	r[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	return t * s * r;
}

glm::mat4 Object::makeModelInverseMatrix() const {
	glm::mat4 t = glm::translate(-translation);
	glm::mat4 s = glm::scale(glm::vec3(1 / scale.x, 1 / scale.y, 1 / scale.z));
	glm::mat4 r = glm::rotation(-rotationAngle, rotationAxis);

	return t * r * s;
}

void Object::setModelUniforms() const {
	shader->setMat4("M", makeModelMatrix());
	shader->setMat4("Minv", makeModelInverseMatrix());
}

void Object::setUniformMaterial() const {
	shader->setVec3("material.ambient", material.ambient);
	shader->setVec3("material.diffuse", material.diffuse);
	shader->setVec3("material.specular", material.specular);
	shader->setFloat("material.shininess", material.shininess);
}

Object::~Object() { delete shader; }
