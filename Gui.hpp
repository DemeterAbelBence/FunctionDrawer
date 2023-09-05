#pragma once

#include "src/gl/Util.hpp"
#include "src/Rect.hpp"

#include "dep/imgui/imgui.h"
#include "dep/imgui/imgui_impl_glfw.h"
#include "dep/imgui/imgui_impl_opengl3.h"

#include "Scene.hpp"

#include <iostream>
#include <Windows.h>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

namespace Gui {
	void drawMaterialPicker(Scene& scene);
	void drawLightPicker(Scene& scene);
	void drawListBox(Scene& scene);
	void drawRectangle(glm::vec3 color);
	void drawFunctionPicker(Scene& scene);

	void drawUserInteface(Scene& scene, int sceneWidth, int windowWidth, int windowHeight);
}