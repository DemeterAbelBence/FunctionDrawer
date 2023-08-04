#include "Scene.hpp"

Scene::Scene() {
	center = glm::vec3(0.0f, 0.0f, 0.0f);

	light = {
		glm::vec3(0.0f, 2.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(0.4f, 0.4f, 0.4f)
	};

	camera.createViewMatrix();

	gridShader = new GpuProgram();
	gridShader->readFragmentSource("src/shaders/gridFragment.shader");
	gridShader->readVertexSource("src/shaders/gridVertex.shader");

	surfaceShader = new GpuProgram();
	surfaceShader->readFragmentSource("src/shaders/fragment1.shader");
	surfaceShader->readVertexSource("src/shaders/vertex1.shader");
}

void Scene::create() {
	float scale = 3.0f;

	Lighting::Material material1 = {
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.2f, 0.2f, 0.2f),
		1.5f
	};

	Lighting::Material material2 = {
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.7f, 0.7f, 0.0f),
		glm::vec3(0.2f, 0.2f, 0.2f),
		1.5f
	};

	gridShader->createProgram();
	gridShader->bind();
	camera.setUniforms(*gridShader);

	surfaceShader->createProgram();
	surfaceShader->bind();
	camera.setUniforms(*surfaceShader);
	surfaceShader->setVec3("light.position", light.position);
	surfaceShader->setVec3("light.diffuse", light.diffuse);
	surfaceShader->setVec3("light.ambient", light.ambient);

	Grid* grid = new Grid();
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

	Sphere* sun = new Sphere(20, 20);
	sun->setMaterial(material1);
	sun->setShader(surfaceShader);
	sun->setScale(1.0f);
	sun->setCenter(light.position);
	sun->setRadius(0.2f);
	sun->create();

	objects.push_back(sun);
	objects.push_back(function);
	objects.push_back(grid);
}

void Scene::draw() const {
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