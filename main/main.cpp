#include <iostream>

#include "Application.hpp"

int main(void) {
    GLFWwindow* window = nullptr;
    try {
        window = Application::initGlfwWindow("FunctionDrawer");
        Application::initOpenGl();
        Application::initImgui(window);
    }
    catch (const char* exception) {
        std::cout << exception << std::endl;
        return 0;
    }

    Application::renderLoop(window);

    return 0;
}