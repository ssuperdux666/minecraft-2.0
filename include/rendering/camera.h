#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Camera {
    public:
        glm::vec3 camPosition;

        glm::vec3 camDirection;
        glm::vec3 camTarget;

        glm::vec3 camUp;
        glm::vec3 camRight;

        const float cameraSpeed = 3.00f;

        Camera();

        void processInput(GLFWwindow *window, float deltaTime);

};

#endif