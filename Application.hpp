#pragma once

#include "src/gl/Util.hpp"

#include "dep/imgui/imgui.h"
#include "dep/imgui/imgui_impl_glfw.h"
#include "dep/imgui/imgui_impl_opengl3.h"

#include "Scene.hpp"
#include "Gui.hpp"

#include <iostream>
#include <Windows.h>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

namespace Application {
	const unsigned int windowWidth = 1200;
	const unsigned int windowHeight = 800;

	const unsigned int sceneWidth = 800;
	const unsigned int sceneHeight = 800;

	GLFWwindow* initGlfwWindow(const char* windowName);
	void initOpenGl();
	void initImgui(GLFWwindow* window);
	void renderLoop(GLFWwindow* window);
}