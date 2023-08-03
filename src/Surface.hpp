#pragma once

#include "Object.hpp"

struct VertexData {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
};

class Surface : public Object {

private:
	unsigned int verticesPerStrip;
	unsigned int strips;
	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
	float scale;

public:
	Surface(unsigned int N, unsigned int M);
	inline void setCenter(glm::vec3 value) { center = value; }
	inline void setScale(float value) { scale = value; }
	VertexData generateVertexData(float x, float y);

	void create() override;
	void draw() const override;

	virtual void eval(float x, float y, glm::vec3& pos, glm::vec3& norm) = 0;
};