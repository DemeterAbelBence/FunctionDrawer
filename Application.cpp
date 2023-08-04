#include "Application.hpp"

GLFWwindow* Application::initGlfwWindow(const char* windowName) {

    if (!glfwInit())
        throw "Glfw initialization error!\n";

    GLFWwindow* window;
    window = glfwCreateWindow(windowWidth, windowHeight, windowName, NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw "Glfw window creation error!\n";
    }
    glfwMakeContextCurrent(window);
    return window;
}

void Application::initOpenGl() {
    GLenum err = glewInit();
    std::cout << "Glew message: " << glewGetErrorString(err) << std::endl << std::endl;
    Util::displayOpenGlInfo();
    Util::initializeDebugContext();

    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    glDebugMessageCallback(&Util::outputDebugMessage, (const void*)NULL);
}

void Application::initImgui(GLFWwindow* window) {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    ImGui_ImplGlfw_InitForOpenGL(window, true); 
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void Application::drawLoop(GLFWwindow* window) {
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

        //draw elements
        glViewport(0, 0, sceneWidth, sceneHeight);
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
        scene.update(window);
        scene.draw();

        glViewport(sceneWidth, 0, windowWidth - sceneWidth, windowHeight);
        glClearColor(0.3f, 0.3f, 0.5f, 1.0f);
        handleUserInteface(scene);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        currentTime = glfwGetTime();
        deltaTime = (currentTime - previousTime);
        if (frameTime - deltaTime > 0)
            Sleep(frameTime - deltaTime);
    }

    glfwTerminate();
}

void Application::handleUserInteface(Scene& scene) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    const char* items[] = { "lightsource", "function", "grid", "everything"};
    static int currentItem;
    ImGui::SetNextWindowSize(ImVec2(250, 120));
    ImGui::SetNextWindowPos(ImVec2(850, 50), ImGuiCond_Always);
    ImGui::Begin("Select object");
    ImGui::ListBox("Objects", &currentItem, items, IM_ARRAYSIZE(items));
    ImGui::End();
    scene.setObjectIndex(currentItem);

    /*ImGui::SetNextWindowSize(ImVec2(120, 60));
    ImGui::SetNextWindowPos(ImVec2(850, 150), ImGuiCond_Always);
    ImGui::Begin("Hello, worl2!");
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(120, 60));
    ImGui::SetNextWindowPos(ImVec2(850, 250), ImGuiCond_Always);
    ImGui::Begin("Hello, worl3!");
    ImGui::End();*/

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

