#pragma once

#include "gl/GpuProgram.hpp"
#include <glm.hpp>

class Camera {

private:
	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;

	glm::mat4 projection;
	glm::mat4 view;

public:
	Camera();

	inline void setEye(glm::vec3 value) { eye = value; }
	inline void setTarget(glm::vec3 value) { target = value; }
	inline void setUp(glm::vec3 value) { up = value; }

	inline glm::vec3 getEye() const { return eye; }
	inline glm::mat4 getProjection() const { return projection; }
	inline glm::mat4 getView() const { return view; }

	void createViewMatrix();
	void update();
	void setUniforms(const GpuProgram& program) const;
};