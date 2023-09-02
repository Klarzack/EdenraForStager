#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <iostream>

void framebufferSize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

std::string loadShaderSource(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Failed to open " << filename << std::endl;
        return "";
    }
    std::string line;
    std::string shaderSource;
    while (std::getline(file, line)) {
        shaderSource += line + '\n';
    }
    file.close();
    return shaderSource;
}

GLuint createShaderProgram(const char* vShaderSource, const char* fShaderSource) {
    int success{};
    char infoLog[512];
    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShaderSource, NULL);
    glCompileShader(vShader);
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShader, 512, NULL, infoLog);
        std::cerr << "Vertex shader failed to compile! " << infoLog << std::endl;
    }
    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fShaderSource, NULL);
    glCompileShader(fShader);
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fShader, 512, NULL, infoLog);
        std::cerr << "Fragment shader failed to compile! " << infoLog << std::endl;
    }
    unsigned int sProgram = glCreateProgram();
    glAttachShader(sProgram, vShader);
    glAttachShader(sProgram, fShader);
    glLinkProgram(sProgram);
    glGetProgramiv(sProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(sProgram, 512, NULL, infoLog);
        std::cerr << "Shader program failed to link! " << infoLog << std::endl;
    }
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    return sProgram;
}

void createBufferObjects(GLenum bufferType, GLuint nrOfIDs, GLuint& bufferName, GLsizeiptr size, const void* data, GLenum usage) {
    glGenBuffers(nrOfIDs, &bufferName);
    glBindBuffer(bufferType, bufferName);
    glBufferData(bufferType, size, data, usage);
}

void createVertexArrays(GLuint nrOfIDs, GLuint& objectName) {
    glGenVertexArrays(nrOfIDs, &objectName);
    glBindVertexArray(objectName);
}

void interpretData(GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer, GLuint attribIndex) {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(attribIndex);
}

void unbindObjects(GLenum target) {
    if (target == GL_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER) {
        glBindBuffer(target, 0);
    }
    else if (target == GL_VERTEX_ARRAY) {
        glBindVertexArray(0);
    }
}