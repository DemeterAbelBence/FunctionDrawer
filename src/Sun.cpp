#include "Sun.hpp"



Sun::Sun(glm::vec3 _center) : Sphere (20, 20) {
	light = {
		_center,
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(0.4f, 0.4f, 0.4f)
	};
	setCenter(_center);
}

Sun::Sun(unsigned int N, unsigned int M, glm::vec3 _center) : Sphere(N, M) {
	light = {
		_center,
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(0.4f, 0.4f, 0.4f)
	};
	setCenter(_center);
}

inline void Sun::translateX(float speed) {
	translation.x += speed;
	light.position.x += speed;
}

inline void Sun::translateY(float speed) {
	translation.y += speed;
	light.position.y += speed;
}

inline void Sun::translateZ(float speed) {
	translation.z += speed;
	light.position.z += speed;
}

void Sun::setUniformLight() const { 
	shader->bind();
	shader->setVec3("light.position", light.position);
	shader->setVec3("light.diffuse", light.diffuse);
	shader->setVec3("light.ambient", light.ambient);
}
