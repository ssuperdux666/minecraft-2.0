#include "rendering/buffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

typedef unsigned long long size_t;

//VAO
VAO::VAO() {
    glGenVertexArrays(1, &ID); 
    glBindVertexArray(ID);
}

void VAO::Bind() {
    glBindVertexArray(ID);
}

//VBO
VBO::VBO() {
    glGenBuffers(1,&ID);
    glBindBuffer(GL_ARRAY_BUFFER,ID);
}

VBO::VBO(const float vertices[], size_t sizeOfVertices) {
    glGenBuffers(1,&ID);
    glBindBuffer(GL_ARRAY_BUFFER,ID);

    glBufferData(GL_ARRAY_BUFFER,sizeOfVertices,vertices,GL_STATIC_DRAW);
}


void VBO::insert_data(const float vertices[], size_t sizeOfVertices) {
    Bind();
    glBufferData(GL_ARRAY_BUFFER,sizeOfVertices,vertices,GL_STATIC_DRAW);
}

void VBO::insert_data(std::vector<float> vertices, size_t sizeOfVertices) {
    Bind();
    glBufferData(GL_ARRAY_BUFFER,sizeOfVertices,vertices.data(),GL_STATIC_DRAW);
}

void VBO::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

//EBO
EBO::EBO() {
    glGenBuffers(1,&ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ID);
}

EBO::EBO(const unsigned int indices[], size_t sizeOfIndices) {
    glGenBuffers(1,&ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ID);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW); 
}

void EBO::insert_data(const float indices[], size_t sizeOfIndices) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);
}