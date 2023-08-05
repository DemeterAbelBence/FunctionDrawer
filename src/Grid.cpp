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

	std::vector<glm::vec3> gridPoints;
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
	vertexBuffer.setData((const void*)&gridPoints[0], numberOfPoints * sizeof(glm::vec3));
	vertexBufferLayout.push(GL_FLOAT, 3);
	vertexArray.addBuffer(vertexBuffer, vertexBufferLayout);
}

void Grid::draw() const {
	vertexArray.bind();
	vertexArray.addBuffer(vertexBuffer, vertexBufferLayout);

	shader->bind();
	setModelUniforms();
	setUniformMaterial();

	glDrawArrays(GL_LINES, 0, numberOfPoints);
}
