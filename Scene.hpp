#include "src/gl/GpuProgram.hpp"
#include "src/gl/VertexArray.hpp"
#include "src/Object.hpp"
#include "src/Grid.hpp"
#include "src/Function.hpp"
#include "src/lighting/Lighting.hpp"
#include "src/Camera.hpp"
#include "src/Sphere.hpp"

#include <GLFW/glfw3.h>

class Scene {

private:
	std::vector<Object*> objects;	
	Lighting::LightSource light;
	Camera camera;

	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);

	GpuProgram* gridShader;
	GpuProgram* surfaceShader;

	unsigned int objectIndex = 3;

public:
	Scene();
	inline void setObjectIndex(unsigned int value) { objectIndex = value; }
	void create();
	void draw() const;
	void update(GLFWwindow* window);
};