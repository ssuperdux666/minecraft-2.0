#include "rendering/shader.h"
#include <config/config.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

std::string loadShader(const std::string& path) {
    std::ifstream file(path); //open de file via de path

    if (!file.is_open()) {//check of het werkt
        throw std::runtime_error("Could not open shader file: " + path);
    }

    std::stringstream ss; //een string maar dan voor een stream van data

    ss << file.rdbuf(); //doet de stream van data van de file in de stringstream

    return ss.str();// maak het gwn een string en go
}

Shader::Shader() {
    std::string vertexShaderSource = loadShader(Graphics_Config::vertexShaderPath);
    std::string fragmentShaderSource = loadShader(Graphics_Config::fragmentShaderPath);

    const char* vertexShaderSourceC = vertexShaderSource.c_str();
    const char* fragmentShaderSourceC = fragmentShaderSource.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourceC, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "failed to compile vertex shader... " << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSourceC,NULL);
    glCompileShader(fragmentShader);

    int success2;
    char infoLog2[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success2);

    if (!success2) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog2);
        std::cerr << "failed to compile fragment shader... " << infoLog2 << std::endl;
    }

    ID = glCreateProgram(); 

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    int success3;
    char infoLog3[512];
    glGetProgramiv(ID,GL_LINK_STATUS,&success3);

    if (!success3) {
        glGetProgramInfoLog(ID,512,NULL,infoLog3);
        std::cout << "failed to link shader program... " << infoLog3 << std::endl;
    }
    //shader program

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Use() {
    glUseProgram(ID); 
}