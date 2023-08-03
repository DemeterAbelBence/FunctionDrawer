#pragma once

#include "Function.hpp"

Function::Function() : Surface(20, 20) {}

Function::Function(unsigned int N, unsigned int M) : Surface(N, M) {}

void Function::eval(float x, float y, glm::vec3& pos, glm::vec3& norm) {
	float z = x * x + y * y;
	pos = glm::vec3(x, z, y);
	norm = glm::vec3(-2.0f * x, 2.0f * y, 1.0f);
}

void Function::setUniformMaterial(const GpuProgram& program) const {
	program.setVec3("material.ambient", material.ambient);
	program.setVec3("material.diffuse", material.diffuse);
	program.setVec3("material.specular", material.specular);
	program.setFloat("material.shininess", material.shininess);
}
