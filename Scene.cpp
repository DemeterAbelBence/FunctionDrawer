#include "Scene.hpp"

Scene::Scene() {
	center = glm::vec3(-1.0f, -1.0f, 1.0f);
	camera.createViewMatrix();

	gridShader = new GpuProgram();
	gridShader->readFragmentSource("src/shaders/gridFragment.shader");
	gridShader->readVertexSource("src/shaders/gridVertex.shader");

	functionShader = new GpuProgram();
	functionShader->readFragmentSource("src/shaders/functionFragment.shader");
	functionShader->readVertexSource("src/shaders/functionVertex.shader");

	sunShader = new GpuProgram();
	sunShader->readFragmentSource("src/shaders/sunFragment.shader");
	sunShader->readVertexSource("src/shaders/sunVertex.shader");
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
	camera.setUniforms(*gridShader);

	functionShader->createProgram();
	camera.setUniforms(*functionShader);

	sunShader->createProgram();
	camera.setUniforms(*sunShader);

	Grid* grid = new Grid(6);
	grid->setShader(gridShader);
	grid->setScale(scale);
	grid->setCenter(center);
	grid->create();

	Function* function = new Function(30, 30);
	function->setMaterial(material2);
	function->setShader(functionShader);
	function->setScale(2.0f);
	float offset = scale / 2.0f;
	function->setCenter(center + glm::vec3(offset, 0.0f, offset));
	function->create();

	sun = new Sun(20, 20, center + glm::vec3(1.5f, 1.0f, 0.0f));
	sun->setMaterial(material1);
	sun->setShader(sunShader);
	sun->setScale(1.0f);
	sun->setRadius(0.1f);
	sun->create();

	objects.push_back(sun);
	objects.push_back(function);
	objects.push_back(grid);
}

void Scene::draw() const {
	sun->setUniformLight(*functionShader);
	camera.setUniforms(*functionShader);
	camera.setUniforms(*gridShader);
	camera.setUniforms(*sunShader);

	for (const auto& object : objects)
		object->draw();
}

void Scene::update(GLFWwindow* window) {
	float speed = 0.05f;
	int sign = 0;
	bool recreate = false;
	void(Transformable::*transformation)(float) = nullptr;

	static glfw::Key keyDown(GLFW_KEY_DOWN);
	static glfw::Key keyUp(GLFW_KEY_UP);
	static glfw::Key keyLeft(GLFW_KEY_LEFT);
	static glfw::Key keyRight(GLFW_KEY_RIGHT);
	static glfw::Key keyW(GLFW_KEY_W);
	static glfw::Key keyS(GLFW_KEY_S);
	static glfw::Key keyA(GLFW_KEY_A);
	static glfw::Key keyD(GLFW_KEY_D);

	if (keyDown.isPressed(window)) {
		transformation = &Transformable::translateY; sign = -1;
	}else if (keyDown.isReleased(window)) { recreate = true; }

	if (keyUp.isPressed(window)) {
		transformation = &Transformable::translateY; sign = 1;
	}else if (keyUp.isReleased(window)) { recreate = true; }

	if (keyRight.isPressed(window)) {
		transformation = &Transformable::translateX; sign = 1;
	}else if (keyRight.isReleased(window)) { recreate = true; }

	if (keyLeft.isPressed(window)) {
		transformation = &Transformable::translateX; sign = -1;
	}else if (keyLeft.isReleased(window)) { recreate = true; }

	if (keyW.isPressed(window)) {
		transformation = &Transformable::translateZ; sign = 1;
	}else if (keyW.isReleased(window)) { recreate = true; }

	if (keyS.isPressed(window)) {
		transformation = &Transformable::translateZ; sign = -1;
	}else if (keyS.isReleased(window)) { recreate = true; }

	if (keyA.isPressed(window)) {
		transformation = &Transformable::rotate; sign = -1; speed = 0.5f;
	}else if (keyA.isReleased(window)) { recreate = true; }
	
	if (keyD.isPressed(window)) {
		transformation = &Transformable::rotate; sign = 1; speed = 0.5f;
	}else if (keyD.isReleased(window)) { recreate = true; }

	if (sign != 0) { 
		if (objectIndex == 3) {
			for (const auto& object : objects)
				(object->*transformation)((float)speed * sign);
		}
		else (objects[objectIndex]->*transformation)((float)speed * sign);
	}

	if (recreate) {
		for (const auto& object : objects)
			object->reCreate();
	}
}

Scene::~Scene() {
	delete gridShader;
	delete functionShader;
	delete sunShader;
}
