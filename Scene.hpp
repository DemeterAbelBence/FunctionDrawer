#pragma once

#include "src/gl/GpuProgram.hpp"
#include "src/gl/VertexArray.hpp"
#include "src/Object.hpp"
#include "src/Grid.hpp"
#include "src/Function.hpp"
#include "src/lighting/Lighting.hpp"
#include "src/Camera.hpp"
#include "src/Sun.hpp"
#include "src/glfw/glfw.hpp"

#include <GLFW/glfw3.h>

class Scene {

private:
	std::vector<Object*> objects;
	Sun* sun;
	Function* function;
	Camera camera;

	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);

	GpuProgram* gridShader;
	GpuProgram* functionShader;
	GpuProgram* sunShader;

	unsigned int objectIndex = 3;

public:
	Scene();

	inline void setObjectIndex(unsigned int value) { objectIndex = value; }
	inline void setFunctionMaterial(const Lighting::Material _material) { function->setMaterial(_material); }
	inline void setLightAmbient(glm::vec3 ambient) { sun->setLightAmbient(ambient); }
	inline void setLightDiffuse(glm::vec3 diffuse) { sun->setLightAmbient(diffuse); }

	void create();
	void draw() const;
	void update(GLFWwindow* window);

	~Scene();	
};