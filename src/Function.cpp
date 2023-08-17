#pragma once

#include "Function.hpp"

Function::Function() : Surface(20, 20) {}

Function::Function(unsigned int N, unsigned int M) : Surface(N, M) {}

void Function::eval(float x, float y, glm::vec3& pos, glm::vec3& norm) {
	float z = sinf(3.14 * x) + cosf(3.14 * y);
	pos = glm::vec3(x, z, y);

	glm::vec3 n = glm::vec3(3.14 * cosf(3.14 * x), 1.0f, -3.14 * sinf(3.14 * y));
	norm = glm::normalize(-n);

	/*float u = x * 2 * (float)3.14157;
	float v = y * (float)3.14157;
	float r = 1.0f;

	pos.x = r * sinf(u) * cosf(v) + center.x;
	pos.y = r * sinf(u) * sinf(v) + center.y;
	pos.z = r * cosf(u) + center.z;

	norm = glm::normalize(pos - center);*/
}

