#pragma once

#include "Object.hpp"

class Grid : public Object{

private:
	unsigned int N = 6;
	unsigned int numberOfPoints = 0;
	float scale;

	std::vector<glm::vec3> gridPoints;

public:
	Grid();
	Grid(unsigned int _N);
	inline void setScale(float value) { scale = value; }

	void create() override;
	void draw() const override;
	void reCreate() override;

private:
	void setBufferData(const void* data, unsigned int size);
};