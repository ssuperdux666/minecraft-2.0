#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include "glm/glm.hpp"
#include <vector>

namespace Graphics_Config {
    constexpr float SCREEN_WIDTH = 1000.0f;
    constexpr float SCREEN_HEIGHT = 800.0f;

    constexpr const char* vertexShaderPath = "../shaderSource/vertex.glsl";
    constexpr const char* fragmentShaderPath = "../shaderSource/fragment.glsl";

    constexpr float FOV = glm::radians(90.0f);
}

namespace World {

    constexpr int SUB_CHUNK_SIZE = 16;
    constexpr int SUB_CHUNK_LENGTH = SUB_CHUNK_SIZE * SUB_CHUNK_SIZE * SUB_CHUNK_SIZE;

}


#endif