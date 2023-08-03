#include "Sphere.hpp"

Sphere::Sphere(unsigned int N, unsigned int M) : Surface(N, M) {
	radius = 0.8f;
	center = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Sphere::eval(float x, float y, glm::vec3& pos, glm::vec3& norm) {
	float u = x * 2 * (float)3.14157;
	float v = y * (float)3.14157;

	pos.x = radius * sinf(u) * cosf(v) + center.x;
	pos.y = radius * sinf(u) * sinf(v) + center.y;
	pos.z = radius * cosf(u) + center.z;

	norm = glm::normalize(pos - center);
}

void Sphere::setUniformMaterial(const GpuProgram& program) const {
	program.setVec3("material.ambient", material.ambient);
	program.setVec3("material.diffuse", material.diffuse);
	program.setVec3("material.specular", material.specular);
	program.setFloat("material.shininess", material.shininess);
}
