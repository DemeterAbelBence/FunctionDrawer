#include "Sphere.hpp"

Sphere::Sphere() : Surface(20, 20) { radius = 1.0f; }

Sphere::Sphere(unsigned int N, unsigned int M) : Surface(N, M) {
	radius = 1.0f;
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