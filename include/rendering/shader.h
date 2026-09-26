#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
  


class Shader {
    public:
        unsigned int ID;

        Shader();

        void Use();
};

#endif