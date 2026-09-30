#ifndef BUFFER_H
#define BUFFER_H

#include<vector>

typedef unsigned long long size_t;

class VAO {
    public:
        unsigned int ID;

        VAO();

        void Bind();
};

class VBO {
    public:
        unsigned int ID;

        VBO();
        VBO(const float vertices[], size_t sizeOfVertices);

        void insert_data(const float vertices[], size_t sizeOfVertices);
        void insert_data(std::vector<float> vertices, size_t sizeOfVertices);

        void Bind();
};

class EBO {
    public:
        unsigned int ID;

        EBO();
        EBO(const unsigned int indices[], size_t sizeOfVertices);

        void insert_data(const float indices[], size_t sizeOfVertices);
};


#endif