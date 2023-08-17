#include "Grid.hpp"

Grid::Grid() { N = 6; }

Grid::Grid(unsigned int _N) { N = _N; }

void Grid::create() {
	std::vector<glm::vec3> axisX;
	std::vector<glm::vec3> axisY;
	std::vector<glm::vec3> axisZ;

	for (int i = 0; i < N; ++i) {
		axisX.push_back(glm::vec3(center.x + scale * (float)i / N, center.y, center.z));
		axisY.push_back(glm::vec3(center.x, center.y + scale * (float)i / N, center.z));
		axisZ.push_back(glm::vec3(center.x, center.y, center.z + scale * (float)i / N));
	}

	for (int i = 0; i < axisX.size(); ++i) {
		glm::vec3 ax = axisX[i];
		glm::vec3 ay = axisY[i];
		glm::vec3 az = axisZ[i];

		//X - plane
		gridPoints.push_back(glm::vec3(ax.x, ax.y, ax.z));
		gridPoints.push_back(glm::vec3(ax.x, ax.y, ax.z + scale));
		gridPoints.push_back(glm::vec3(az.x, az.y, az.z));
		gridPoints.push_back(glm::vec3(az.x + scale, az.y, az.z));

		//Y - plane
		gridPoints.push_back(glm::vec3(ay.x, ay.y, ay.z));
		gridPoints.push_back(glm::vec3(ay.x, ay.y, ay.z + scale));
		gridPoints.push_back(glm::vec3(az.x, az.y, az.z));
		gridPoints.push_back(glm::vec3(az.x, az.y + scale, az.z));

		//Z - plane
		gridPoints.push_back(glm::vec3(ay.x, ay.y, ay.z + scale));
		gridPoints.push_back(glm::vec3(ay.x + scale, ay.y, ay.z + scale));
		gridPoints.push_back(glm::vec3(ax.x, ax.y, ax.z + scale));
		gridPoints.push_back(glm::vec3(ax.x, ax.y + scale, ax.z + scale));
	}

	numberOfPoints = gridPoints.size();
	setBufferData((const void*)&gridPoints[0], numberOfPoints * sizeof(glm::vec3));
}

void Grid::draw() const {
	vertexArray.bind();
	vertexArray.addBuffer(vertexBuffer, vertexBufferLayout);

	shader->bind();
	setAllUniforms();

	glDrawArrays(GL_LINES, 0, numberOfPoints);
}

void Grid::reCreate() {
	unsigned int size = gridPoints.size();
	for (int i = 0; i < size; ++i) {
		glm::vec4 p = glm::vec4(gridPoints[i], 1.0f) * makeModelMatrix();
		gridPoints[i] = glm::vec3(p);
	}
	setBufferData((const void*)&gridPoints[0], size * sizeof(glm::vec3));
	resetTransormations();
}

void Grid::setBufferData(const void* data, unsigned int size) {
	vertexBuffer.setData(data, size);

	if (!getCeated()) {
		vertexBufferLayout.push(GL_FLOAT, 3);
		vertexArray.addBuffer(vertexBuffer, vertexBufferLayout);
		setCreated(true);
	}
}
