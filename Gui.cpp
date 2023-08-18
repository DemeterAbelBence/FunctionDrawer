#include "Gui.hpp"

void Gui::drawMaterialPicker(Scene& scene) {
    static float ambient[3] = {0.0f, 0.0f, 0.5f};
    static float diffuse[3] = {0.4f, 0.4f, 0.4f};
    static float specular[3] = {0.2f, 0.2f, 0.2f};
    static float shininess = 1.0f;

    ImGui::SetNextWindowSize(ImVec2(300, 130));
    ImGui::SetNextWindowPos(ImVec2(850, 200), ImGuiCond_Always);
    ImGui::Begin("Material properties");
    ImGui::SliderFloat3("ambient", &ambient[0], 0.0f, 1.0f, "%.2f", 0);
    ImGui::SliderFloat3("diffuse", &diffuse[0], 0.0f, 1.0f, "%.2f", 0);
    ImGui::SliderFloat3("specular", &specular[0], 0.0f, 1.0f, "%.2f", 0);
    ImGui::SliderFloat("shininess", &shininess, 0.1f, 1.0f, "%.2f", 0);
    ImGui::End();

    Lighting::Material material = {
        glm::vec3(ambient[0], ambient[1], ambient[2]),
        glm::vec3(diffuse[0], diffuse[1], diffuse[2]),
        glm::vec3(specular[0], specular[1], specular[2]),
        shininess
    };

    scene.setFunctionMaterial(material);
}

void Gui::drawLightPicker(Scene& scene) {
    static float ambient[3] = { 1.0f, 1.0f, 1.0f };
    static float diffuse[3] = { 0.4f, 0.4f, 0.4f };

    ImGui::SetNextWindowSize(ImVec2(300, 120));
    ImGui::SetNextWindowPos(ImVec2(850, 350), ImGuiCond_Always);
    ImGui::Begin("Light properties");
    ImGui::SliderFloat3("ambient", &ambient[0], 0.0f, 1.0f, "%.2f", 0);
    ImGui::SliderFloat3("diffuse", &diffuse[0], 0.0f, 1.0f, "%.2f", 0);
    ImGui::End();

    scene.setLightAmbient(glm::vec3(ambient[0], ambient[1], ambient[2]));
    scene.setLightDiffuse(glm::vec3(diffuse[0], diffuse[1], diffuse[2]));
}

void Gui::drawListBox(Scene& scene) {
    const char* items[] = { "lightsource", "function", "grid", "everything" };
    static int currentItem;
    ImGui::SetNextWindowSize(ImVec2(300, 120));
    ImGui::SetNextWindowPos(ImVec2(850, 50), ImGuiCond_Always);
    ImGui::Begin("Select object");
    ImGui::ListBox("Objects", &currentItem, items, IM_ARRAYSIZE(items));
    ImGui::End();
    scene.setObjectIndex(currentItem);
}

void Gui::drawRectangle(glm::vec3 color) {
    static Rect rectangle(glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f), color);
    rectangle.draw();
}

void Gui::drawUserInteface(Scene& scene, int sceneWidth, int windowWidth, int windowHeight) {
    glViewport(sceneWidth, 0, windowWidth - sceneWidth, windowHeight);
    drawRectangle(glm::vec3(0.2f, 0.2f, 0.3f));

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    drawListBox(scene);
    drawMaterialPicker(scene);
    drawLightPicker(scene);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}