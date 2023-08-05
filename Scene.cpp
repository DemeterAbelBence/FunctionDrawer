#include "Scene.hpp"

Scene::Scene() {
	center = glm::vec3(0.0f, 0.0f, 0.0f);

	camera.createViewMatrix();

	gridShader = new GpuProgram();
	gridShader->readFragmentSource("src/shaders/gridFragment.shader");
	gridShader->readVertexSource("src/shaders/gridVertex.shader");

	surfaceShader = new GpuProgram();
	surfaceShader->readFragmentSource("src/shaders/functionFragment.shader");
	surfaceShader->readVertexSource("src/shaders/functionVertex.shader");
}

void Scene::create() {
	float scale = 3.0f;

	Lighting::Material material1 = {
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.2f, 0.2f, 0.2f),
		5.0f
	};

	Lighting::Material material2 = {
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.7f, 0.0f, 0.0f),
		glm::vec3(0.2f, 0.2f, 0.2f),
		1.0f
	};

	gridShader->createProgram();
	gridShader->bind();
	camera.setUniforms(*gridShader);

	surfaceShader->createProgram();
	surfaceShader->bind();
	camera.setUniforms(*surfaceShader);

	Grid* grid = new Grid(6);
	grid->setShader(gridShader);
	grid->setScale(scale);
	grid->setCenter(center);
	grid->create();

	Function* function = new Function(20, 20);
	function->setMaterial(material2);
	function->setShader(surfaceShader);
	function->setScale(1.0f);
	float offset = scale / 2.0f;
	function->setCenter(center + glm::vec3(offset, 0.0f, offset));
	function->create();

	sun = new Sun(20, 20, glm::vec3(0.0f, 2.0f, 0.0f));
	sun->setMaterial(material1);
	sun->setShader(surfaceShader);
	sun->setScale(1.0f);
	sun->setRadius(0.2f);
	sun->create();

	objects.push_back(sun);
	objects.push_back(function);
	objects.push_back(grid);
}

void Scene::draw() const {
	sun->setUniformLight();
	for (const auto& object : objects)
		object->draw();
}

void Scene::update(GLFWwindow* window) {
	float rotateSpeed = 2.0f;
	float moveSpeed = 0.05f;
	int sign = 0;
	void(Object::*transformation)(float) = nullptr;

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		transformation = &Object::translateX; sign = -1;
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		transformation = &Object::translateX; sign = 1;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		transformation = &Object::translateY; sign = 1;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		transformation = &Object::translateY; sign = -1;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		transformation = &Object::translateZ; sign = 1;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		transformation = &Object::translateZ; sign = -1;
	}

	if (sign != 0) { 
		if (objectIndex == 3) {
			for (const auto& object : objects)
				(object->*transformation)((float)moveSpeed * sign);
		}
		else (objects[objectIndex]->*transformation)((float)moveSpeed * sign);
	}
}