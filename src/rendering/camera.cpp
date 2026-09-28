#include "rendering/camera.h"


Camera::Camera() {
    camPosition = glm::vec3(0.0f, 0.0f ,1.0f);
    
    camTarget = glm::vec3(0.0f, 0.0f ,0.0f);

    camDirection = glm::normalize(camTarget - camPosition);

    camUp = glm::vec3(0.0f,1.0f,0.0f);

    camRight = glm::normalize(glm::cross(camUp, camDirection));

    camUp = glm::normalize(glm::cross(camDirection, camRight));
}

void Camera::process_input(GLFWwindow *window, float deltaTime) {

    float frameSpeed = deltaTime * CAMERA_SPEED;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camPosition += camDirection * frameSpeed;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camPosition -= camDirection * frameSpeed;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camPosition -= glm::normalize(glm::cross(camDirection, camUp)) * frameSpeed;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camPosition += glm::normalize(glm::cross(camDirection, camUp)) * frameSpeed;

    double currentTime = glfwGetTime();

    if ((glfwGetKey(window, DECATIVATION_KEY) == GLFW_PRESS) && (currentTime - lastPress >= 1)) {

        lastPress = currentTime;
        
        locked = !locked;

        glfwSetInputMode(window, GLFW_CURSOR, locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);

        firstMouse = true;
    }

}

void Camera::process_mouse(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camDirection = glm::normalize(direction);
}  