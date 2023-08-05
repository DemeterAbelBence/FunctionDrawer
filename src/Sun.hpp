#pragma once

#include "Sphere.hpp";

class Sun : public Sphere {

private:
	Lighting::LightSource light;

public:
	Sun(glm::vec3 _center);
	Sun(unsigned int N, unsigned int M, glm::vec3 _center);
	virtual inline void translateX(float speed) override;
	virtual inline void translateY(float speed) override;
	virtual inline void translateZ(float speed) override;

	void setUniformLight() const;
};