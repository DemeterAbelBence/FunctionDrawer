#pragma once

#include "Surface.hpp"

class Sphere : public Surface {

private:
	float radius;

public:
	Sphere();
	Sphere(unsigned int N, unsigned int M);
	inline void setRadius(float value) { radius = value; }

	void eval(float u, float v, glm::vec3& pos, glm::vec3& norm) override;
};