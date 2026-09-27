#ifndef CONFIG_H
#define CONFIG_H

#include <string>

namespace Graphics_Config {
    constexpr float SCREEN_WIDTH = 1000.0f;
    constexpr float SCREEN_HEIGHT = 800.0f;

    constexpr const char* vertexShaderPath = "../shaderSource/vertex.glsl";
    constexpr const char* fragmentShaderPath = "../shaderSource/fragment.glsl";
}

#endif