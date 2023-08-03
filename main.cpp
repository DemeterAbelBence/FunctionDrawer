#include "src/gl/Util.hpp"
#include "src/gl/GpuProgram.hpp"
#include "Scene.hpp"

#include <iostream>
#include <Windows.h>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
    // Initialize window
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1000, 800, "Function Drawer", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //initialize opengl
    GLenum err = glewInit();
    std::cout << "Glew message: " << glewGetErrorString(err) << std::endl << std::endl;
    Util::displayOpenGlInfo();
    Util::initializeDebugContext();
    
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    glDebugMessageCallback(&Util::outputDebugMessage, (const void*)NULL);

    //virtual world
    Scene scene;
    scene.create();

    //draw loop
    float currentTime = 0;
    float previousTime = 0;
    float deltaTime = 0;
    const int FPS = 60;
    const float frameTime = (float)1000 / FPS;
    while (!glfwWindowShouldClose(window)) {
        previousTime = currentTime;
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        scene.update(window);
        scene.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
        currentTime = glfwGetTime();
        deltaTime = (currentTime - previousTime);
        if (frameTime - deltaTime > 0)
            Sleep(frameTime - deltaTime);
    }

    /*GpuProgram shader;
    shader.readVertexSource("src/shaders/vertex2.shader");
    shader.readFragmentSource("src/shaders/fragment2.shader");
    shader.createProgram();
    shader.bind();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDepthFunc(GL_EQUAL);
    glDepthRange(0.0f, 2.0f);

    float RED_Z = 1.0f;
    float BLUE_Z = 1.0f;
    float vertices[36] = {
        0.5f, 0.5f, RED_Z,
        1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, RED_Z,
        1.0f, 0.0f, 0.0f,
        0.0f, -0.5f, RED_Z,
        1.0f, 0.0f, 0.0f,

        0.5f, -0.5f, BLUE_Z,
        0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, BLUE_Z,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.5f, BLUE_Z,
        0.0f, 0.0f, 1.0f,
    };

    VertexArray vao;
    VertexBuffer vbo((const void*)vertices, 36 * sizeof(float));
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 3);
    layout.push(GL_FLOAT, 3);
    vao.addBuffer(vbo, layout);
    vao.bind();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, NULL, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }*/

    glfwTerminate();
    return 0;
}