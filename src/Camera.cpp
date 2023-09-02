#include "Camera.hpp"

Camera::Camera() {
	eye = glm::vec3(0.0f, 0.0f, -1.0f);
    target = glm::vec3(0.0f, 0.0f, 1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);

    float nearZ = 0.1f;
    float farZ = 8.0f;
    float zRange = nearZ - farZ;
    float A = (-farZ - nearZ) / zRange;
    float B = 2.0f * farZ * nearZ / zRange;

    projection[0] = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
    projection[1] = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    projection[2] = glm::vec4(0.0f, 0.0f, A, B);
    projection[3] = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);

    view[0] = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
    view[1] = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    view[2] = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
    view[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

void Camera::createViewMatrix() {
    glm::vec3 D = glm::normalize(target - eye);
    glm::vec3 R = glm::normalize(glm::cross(up, D));
    glm::vec3 U = glm::normalize(glm::cross(D, R));

    glm::mat4 rotation;
    rotation[0] = glm::vec4(R, 0.0f);
    rotation[1] = glm::vec4(U, 0.0f);
    rotation[2] = glm::vec4(D, 0.0f);
    rotation[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    glm::mat4 translation;
    translation[0] = glm::vec4(1.0f, 0.0f, 0.0f, -eye.x);
    translation[1] = glm::vec4(0.0f, 1.0f, 0.0f, -eye.y);
    translation[2] = glm::vec4(0.0f, 0.0f, 1.0f, -eye.z);
    translation[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    view = rotation * translation;
}

void Camera::update() {
    static float i = 0;
    float r = 2.0f;

    eye.x = target.x + r * glm::sin(i * 3.14157f);
    eye.y = target.y + r * glm::cos(i * 3.14157f);
    i++;

    createViewMatrix();
}

void Camera::setUniforms(const GpuProgram& program) const {
    program.bind();
    program.setMat4("P", projection);
    program.setMat4("V", view);
    program.setVec3("eye", eye);
}


