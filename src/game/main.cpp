#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "config/config.h"
#include "rendering/shader.h"
#include "rendering/textures.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

unsigned int GLOBAL_DEBUG_INDEX = 0;

GLfloat vertices[32] = {
    // positions          // colors           // tex coords
    -1.0f, -1.0f,  0.0f,   1.0f,  1.0f,  1.0f,   0.0f, 0.0f,
    -1.0f,  1.0f,  0.0f,   1.0f,  1.0f,  1.0f,   0.0f, 1.0f,
     1.0f, -1.0f,  0.0f,   1.0f,  1.0f,  1.0f,   1.0f, 0.0f,
     1.0f,  1.0f,  0.0f,   1.0f,  1.0f,  1.0f,   1.0f, 1.0f,
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

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    shaderProgram.Use();
    glBindVertexArray(VAO);

    Texture tex1("../assets/goon.jpg");

    glm::mat4 trans = glm::mat4(1.0f);

    //trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    
    trans = glm::scale(trans, glm::vec3(0.5, 0.25, 0.5));

    unsigned int transformLoc = glGetUniformLocation(shaderProgram.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Use();

        glBindTexture(GL_TEXTURE_2D, tex1.ID);

        glUseProgram(shaderProgram.ID);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}