#include "Scene.hpp"

Scene::Scene() {
	center = glm::vec3(0.0f, 0.0f, 0.0f);

	Lighting::Material material1 = {
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.2f, 0.2f, 0.2f),
		1.5f
	};
	function.setMaterial(material1);

	light = {
		glm::vec3(0.0f, 5.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(0.4f, 0.4f, 0.4f)
	};

	camera.createViewMatrix();

	gridShader.readFragmentSource("src/shaders/gridFragment.shader");
	gridShader.readVertexSource("src/shaders/gridVertex.shader");

	functionShader.readFragmentSource("src/shaders/fragment1.shader");
	functionShader.readVertexSource("src/shaders/vertex1.shader");
}

void Scene::create() {
	float scale = 3.0f;
	grid.setScale(scale);
	grid.setCenter(center);
	grid.create();

	function.setScale(1.0f);
	float offset = scale / 2.0f;
	function.setCenter(center + glm::vec3(offset, 0.0f, offset));
	function.create();
	VertexData firstVertex = function.generateVertexData(0, 0);
	glm::vec3 p = firstVertex.position;
	glm::vec3 n = firstVertex.normal;
	glm::vec3 axis = n;
	function.setRotationAxis(glm::normalize(axis));

	gridShader.createProgram();
	functionShader.createProgram();
}

void Scene::draw() const {
	gridShader.bind();
	grid.setModelUniforms(gridShader);
	camera.setUniforms(gridShader);
	grid.draw();

	functionShader.bind();
	function.setModelUniforms(functionShader);
	function.setUniformMaterial(functionShader);
	functionShader.setVec3("light.position", light.position);
	functionShader.setVec3("light.diffuse", light.diffuse);
	functionShader.setVec3("light.ambient", light.ambient);
	camera.setUniforms(functionShader);
	function.draw();
}

void Scene::update(GLFWwindow* window) {
	float rotateSpeed = 2.0f;
	float moveSpeed = 0.05f;

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		function.translateX(-moveSpeed);
		grid.translateX(-moveSpeed);
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		function.translateX(moveSpeed);
		grid.translateX(moveSpeed);
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		function.translateY(moveSpeed);
		grid.translateY(moveSpeed);
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		function.translateY(-moveSpeed);
		grid.translateY(-moveSpeed);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		function.translateZ(moveSpeed);
		grid.translateZ(moveSpeed);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		function.translateZ(-moveSpeed);
		grid.translateZ(-moveSpeed);
	}
}