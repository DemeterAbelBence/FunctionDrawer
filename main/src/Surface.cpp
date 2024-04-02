#include "Surface.hpp"

Surface::Surface(unsigned int N, unsigned int M) : Object() {
	verticesPerStrip = (M + 1) * 2;
	strips = N;
}

VertexData Surface::generateVertexData(float x, float y) {
	static int colorIndex = 0;

	glm::vec3 colors[] = {
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	};

	glm::vec3 position;
	glm::vec3 normal;
	eval(x, y, position, normal);
	position = position + center;

	return {position, normal, colors[(colorIndex++) % 3]};
}

void Surface::create() {
	unsigned int N = strips;
	unsigned int M = verticesPerStrip / 2 - 1;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= M; j++) {
			vertexData.push_back(generateVertexData(scale * (float)j / M, scale * (float)i / N));
			vertexData.push_back(generateVertexData(scale * (float)j / M, scale * (float)(i + 1) / N));
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= M; j++) {
			vertexData.push_back(generateVertexData(-scale * (float)j / M, -scale * (float)i / N));
			vertexData.push_back(generateVertexData(-scale * (float)j / M, -scale * (float)(i + 1) / N));
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= M; j++) {
			vertexData.push_back(generateVertexData(scale * (float)j / M, -scale * (float)i / N));
			vertexData.push_back(generateVertexData(scale * (float)j / M, -scale * (float)(i + 1) / N));
		}
	}
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= M; j++) {
			vertexData.push_back(generateVertexData(-scale * (float)j / M, scale * (float)i / N));
			vertexData.push_back(generateVertexData(-scale * (float)j / M, scale * (float)(i + 1) / N));
		}
	}
	setBufferData((const void*)&vertexData[0], vertexData.size() * sizeof(VertexData));
}

void Surface::draw() const {
	vertexArray.bind();
	vertexArray.addBuffer(vertexBuffer, vertexBufferLayout);

	shader->bind();
	setAllUniforms();

	for (unsigned int i = 0; i < 4 * strips; i++) 
		glDrawArrays(GL_TRIANGLE_STRIP, i * verticesPerStrip, verticesPerStrip);
}

void Surface::reCreate() {
	unsigned int size = vertexData.size(); 
	for (int i = 0; i < size; ++i) {
		glm::vec4 p = glm::vec4(vertexData[i].position, 1.0f) * makeModelMatrix();
		glm::vec4 n = makeModelInverseMatrix() * glm::vec4(vertexData[i].normal, 0.0f);
		
		vertexData[i].position = glm::vec3(p);
		vertexData[i].normal = glm::vec3(glm::normalize(n));
	}
	setBufferData((const void*)&vertexData[0], size * sizeof(VertexData));
	resetTransormations();
}

void Surface::setBufferData(const void* data, unsigned int size) {
	vertexBuffer.setData(data, size);
	if (!getCeated()) {
		vertexBufferLayout.push(GL_FLOAT, 3);
		vertexBufferLayout.push(GL_FLOAT, 3);
		vertexBufferLayout.push(GL_FLOAT, 3);
		vertexArray.addBuffer(vertexBuffer, vertexBufferLayout);

		setCreated(true);
	}
}
