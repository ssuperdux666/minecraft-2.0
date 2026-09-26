#ifndef CONFIG_H
#define CONFIG_H

#include <string>

namespace Graphics_Config {
    constexpr unsigned int SCREEN_WIDTH = 1000;
    constexpr unsigned int SCREEN_HEIGHT = 800;

    constexpr const char* vertexShaderPath = "../shaderSource/vertex.glsl";
    constexpr const char* fragmentShaderPath = "../shaderSource/fragment.glsl";
}

#endif