#pragma once

#include "Surface.hpp"

class Sphere : public Surface {

private:
	glm::vec3 center;
	float radius;

	const Lighting::Material material = {
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.2f, 0.2f, 0.2f),
		1.5f
	};

public:
	Sphere(unsigned int N, unsigned int M);
	void eval(float u, float v, glm::vec3& pos, glm::vec3& norm) override;
	void setUniformMaterial(const GpuProgram& program) const override;
};