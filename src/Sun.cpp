#include "Sun.hpp"



Sun::Sun(glm::vec3 _center) : Sphere (20, 20) {
	light = {
		_center,
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f)
	};
	setCenter(_center);
}

Sun::Sun(unsigned int N, unsigned int M, glm::vec3 _center) : Sphere(N, M) {
	light = {
		_center,
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f)
	};
	setCenter(_center);
}

inline void Sun::translateX(float speed) {
	translation.x += speed;
	center.x += speed;
	light.position.x += speed;
}

inline void Sun::translateY(float speed) {
	translation.y += speed;
	center.y += speed;
	light.position.y += speed;
}

inline void Sun::translateZ(float speed) {
	translation.z += speed;
	center.z += speed;
	light.position.z += speed;
}

void Sun::rotate(float speed) {
	Transformable::rotate(speed);
	rotateLight(); 
}

void Sun::setUniformLight(const GpuProgram& progarm) const { 
	progarm.bind();
	progarm.setVec3("light.position", light.position);
	progarm.setVec3("light.diffuse", light.diffuse);
	progarm.setVec3("light.ambient", light.ambient);
}

void Sun::rotateLight() {
	glm::vec4 newLightPosition = makeRotationMatrix() * glm::vec4(light.position, 1.0f);
	light.position = glm::vec3(newLightPosition);
}
