#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "config/config.h"

#include "rendering/shader.h"
#include "rendering/textures.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "rendering/camera.h"

unsigned int GLOBAL_DEBUG_INDEX = 0;
float FOV = glm::radians(90.0f);

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[6] = {
    3, 2, 1, 2, 0, 1
};

void debugPrint(int line) {
    std::cout << "Debug print " << GLOBAL_DEBUG_INDEX << " on line " << line << std::endl;
    GLOBAL_DEBUG_INDEX += 1;
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

    unsigned int VAO;
    glGenVertexArrays(1, &VAO); 
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
    
    Shader shaderProgram;

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    shaderProgram.Use();
    glBindVertexArray(VAO);

    Texture tex1("../assets/goon.jpg");
    Camera mainCam;

    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(1);

    int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
    int modelLoc2 = glGetUniformLocation(shaderProgram.ID, "view");
    int modelLoc3 = glGetUniformLocation(shaderProgram.ID, "projection");

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while (!glfwWindowShouldClose(window)) {

        float currentFrameTime = glfwGetTime();

        float currentFrame = currentFrameTime;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, tex1.ID);

        glUseProgram(shaderProgram.ID);
        glBindVertexArray(VAO);

        mainCam.processInput(window,deltaTime);
        
        //model
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(0.0f,0.0f,0.0f));
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, currentFrameTime * FOV, glm::vec3(1.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

        //view
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(mainCam.camPosition, mainCam.camPosition + mainCam.camDirection, mainCam.camUp);

        //projection
        glm::mat4 projection;
        projection = glm::perspective(FOV, Graphics_Config::SCREEN_WIDTH / Graphics_Config::SCREEN_HEIGHT, 0.1f, 100.0f);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));   
        glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(view)); 
        glUniformMatrix4fv(modelLoc3, 1, GL_FALSE, glm::value_ptr(projection));   

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}