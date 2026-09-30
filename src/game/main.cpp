#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "rendering/buffer.h"

#include "config/config.h"

#include "rendering/shader.h"
#include "rendering/textures.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "rendering/camera.h"

#include "world/cube.h"
#include "world/sub_chunk.h"
#include "world/world.h"

Minecraft_World world1;

unsigned int GLOBAL_DEBUG_INDEX = 0;

Camera mainCam;

void debug_print(int line) {
    std::cout << "Debug print " << GLOBAL_DEBUG_INDEX << " on line " << line << std::endl;
    GLOBAL_DEBUG_INDEX += 1;
}

void mouse_input_func(GLFWwindow* window, double xpos, double ypos) {
    if (mainCam.locked) 
        mainCam.process_mouse(window, xpos, ypos);
}

int main() {

    if (!glfwInit()) {
        std::cerr << "GLFW failed to load..." << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(Graphics_Config::SCREEN_WIDTH,Graphics_Config::SCREEN_HEIGHT,"minecraft",NULL,NULL);

    if (!window) {
        std::cerr << "window failed to create..." << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "glad failed to load..." << std::endl;
    }

    glViewport(0,0,Graphics_Config::SCREEN_WIDTH,Graphics_Config::SCREEN_HEIGHT);

    sub_chunk* chunk1 = new sub_chunk(1,1,1,world1);
    sub_chunk* chunk2 = new sub_chunk(0,0,0,world1);
    sub_chunk* chunk3 = new sub_chunk(-1,-1,-1,world1);

    world1.worldChunks.push_back(chunk1);
    world1.worldChunks.push_back(chunk2);
    world1.worldChunks.push_back(chunk3);

    chunk1->mesh_sub_chunk();
    chunk2->mesh_sub_chunk();
    chunk3->mesh_sub_chunk();

/*  VAO VAO1;
    VBO VBO1(CUBE_VERTICES, sizeof(CUBE_VERTICES));
    EBO EBO1(CUBE_INDICES, sizeof(CUBE_INDICES)); */
    
    Shader shaderProgram;

    shaderProgram.Use();

    Texture tex1("../assets/TEM.jpg");

    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(1);

    int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
    int modelLoc2 = glGetUniformLocation(shaderProgram.ID, "view");
    int modelLoc3 = glGetUniformLocation(shaderProgram.ID, "projection");

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, mouse_input_func); 

    while (!glfwWindowShouldClose(window)) {

        float currentFrameTime = glfwGetTime();

        float currentFrame = currentFrameTime;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mainCam.process_input(window,deltaTime);
            
        for (sub_chunk* chunk : world1.worldChunks) {

            //model
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3((float)chunk->xPosition,(float)chunk->yPosition,(float)chunk->zPosition));
            //view
            glm::mat4 view = glm::mat4(1.0f);
            view = glm::lookAt(mainCam.camPosition, mainCam.camPosition + mainCam.camDirection, mainCam.camUp);
            //projection
            glm::mat4 projection;
            projection = glm::perspective(Graphics_Config::FOV, Graphics_Config::SCREEN_WIDTH / Graphics_Config::SCREEN_HEIGHT, 0.01f, 100.0f);

            glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(view)); 
            glUniformMatrix4fv(modelLoc3, 1, GL_FALSE, glm::value_ptr(projection)); 
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 

            chunk->draw(tex1,shaderProgram);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}