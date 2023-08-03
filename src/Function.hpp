#pragma once

#include "Surface.hpp"
#include "lighting/Lighting.hpp"
#include "gl/GpuProgram.hpp"

class Function : public Surface {

private:
	Lighting::Material material;

public:
	Function();
	Function(unsigned int N, unsigned int M);
	inline void setMaterial(const Lighting::Material& _material) { material = _material; }

	void eval(float u, float v, glm::vec3& pos, glm::vec3& norm) override;
	void setUniformMaterial(const GpuProgram& program) const override;
};