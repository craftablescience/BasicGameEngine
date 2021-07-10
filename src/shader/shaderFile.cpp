#include "shaderFile.h"
#include <glad/gl.h>
#include <iostream>
#include <fstream>
#include <sstream>

shaderFile::shaderFile(unsigned int type, const std::string& source, bool isFilePath) : glObject() {
    this->type = type;
    this->handle = -1;
    if (!isFilePath) {
        this->source = source.c_str();
    } else {
        this->source = shaderFile::loadSourceFromFile(source).c_str();
    }
}

void shaderFile::compile() {
    if (this->handle >= 0) return;
    this->handle = glCreateShader(type);
    glShaderSource(this->handle, 1, &(this->source), nullptr);
    glCompileShader(this->handle);
#if DEBUG
    this->checkForCompilationErrors();
#endif
}

std::string shaderFile::loadSourceFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: shader file at " << filepath << " unreadable!" << std::endl;
        return "";
    } else {
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        std::string data = buffer.str();
        return data;
    }
}

void shaderFile::checkForCompilationErrors() const {
    int success;
    char infoLog[512];
    glGetShaderiv(this->handle, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(this->handle, 512, nullptr, infoLog);
        std::cerr << "Error: shader compilation failed. Type: " << this->type << std::endl;
        std::cerr << infoLog << std::endl;
    }
}

unsigned int shaderFile::getType() const {
    return this->type;
}
