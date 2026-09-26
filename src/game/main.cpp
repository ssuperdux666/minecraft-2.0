#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "config/config.h"
#include "rendering/shader.h"

unsigned int GLOBAL_DEBUG_INDEX = 0;

GLfloat verticies[18] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(Graphics_Config::SCREEN_WIDTH,Graphics_Config::SCREEN_HEIGHT,"sigma",NULL,NULL);

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

    glBufferData(GL_ARRAY_BUFFER,sizeof(verticies),verticies,GL_STATIC_DRAW);

    Shader shaderProgram;

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    shaderProgram.Use();
    glBindVertexArray(VAO);

    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}