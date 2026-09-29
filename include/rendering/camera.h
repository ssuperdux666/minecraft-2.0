#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

const float CAMERA_SPEED = 15.00f;
const int DECATIVATION_KEY = GLFW_KEY_H;

class Camera {
    public:
        glm::vec3 camPosition;

        glm::vec3 camDirection;
        glm::vec3 camTarget;

        glm::vec3 camUp;
        glm::vec3 camRight;

        bool firstMouse = true;
        double lastX;
        double lastY;

        float yaw;
        float pitch;

        bool locked = true;

        float lastPress = 0;

        Camera();

        void process_input(GLFWwindow *window, float deltaTime);
        void process_mouse(GLFWwindow* window, double xpos, double ypos);
};

#endif