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
	float scale;

	std::vector<VertexData> vertexData;

public:
	Surface(unsigned int N, unsigned int M);
	inline void setScale(float value) { scale = value; }
	VertexData generateVertexData(float x, float y);

	void create() override;
	void draw() const override;
	void reCreate() override;

	virtual void eval(float x, float y, glm::vec3& pos, glm::vec3& norm) = 0;

private:
	void setBufferData(const void* data, unsigned int size);
};