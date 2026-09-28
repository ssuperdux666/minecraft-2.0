#include "rendering/camera.h"


Camera::Camera() {
    camPosition = glm::vec3(0.0f, 0.0f ,1.0f);
    
    camTarget = glm::vec3(0.0f, 0.0f ,0.0f);

    camDirection = glm::normalize(camTarget - camPosition);

    camUp = glm::vec3(0.0f,1.0f,0.0f);

    camRight = glm::normalize(glm::cross(camUp, camDirection));

    camUp = glm::normalize(glm::cross(camDirection, camRight));
}

void Camera::processInput(GLFWwindow *window, float deltaTime) {

    float frameSpeed = deltaTime * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camPosition += camDirection * frameSpeed;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camPosition -= camDirection * frameSpeed;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camPosition -= glm::normalize(glm::cross(camDirection, camUp)) * frameSpeed;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camPosition += glm::normalize(glm::cross(camDirection, camUp)) * frameSpeed;

}