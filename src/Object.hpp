#pragma once

#include "gl/VertexArray.hpp"
#include "gl/GpuProgram.hpp"
#include "lighting/Lighting.hpp"

#include <glm.hpp>

class Object {

protected:
	VertexArray vertexArray;
	VertexBuffer vertexBuffer;
	VertexBufferLayout vertexBufferLayout;

private:
	glm::vec3 translation;
	glm::vec3 scale;
	glm::vec3 rotationAxis;
	float rotationAngle;

public:
	Object();

	inline void setTranslation(glm::vec3 t) { translation = t; }
	inline void setScale(glm::vec3 s) { scale = s; }
	inline void setRotationAxis(glm::vec3 r) { rotationAxis = r; }
	inline void setRotationAngle(float r) { rotationAngle = r; }

	inline void translateX(float speed) { translation.x += speed; }
	inline void translateY(float speed) { translation.y += speed; }
	inline void translateZ(float speed) { translation.z += speed; }

	void rotate(float degrees);
	glm::mat4 makeModelMatrix() const;
	glm::mat4 makeModelInverseMatrix() const;
	void setModelUniforms(const GpuProgram& program) const;

	virtual void setUniformMaterial(const GpuProgram& program) const;
	virtual void create() = 0;
	virtual void draw() const = 0;
};