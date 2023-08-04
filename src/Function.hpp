#pragma once

#include "Surface.hpp"
#include "lighting/Lighting.hpp"
#include "gl/GpuProgram.hpp"

class Function : public Surface {

public:
	Function();
	Function(unsigned int N, unsigned int M);

	void eval(float u, float v, glm::vec3& pos, glm::vec3& norm) override;
};