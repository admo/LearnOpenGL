//
// Created by adamo on 2018-02-11.
//

#include <glad/glad.h>
#include <string>

#pragma once

class Shader {
public:
    unsigned int id;

    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float) const;

private:
    std::string readShader(const GLchar *path) const;
    int compileShader(const char *shaderCode, int shaderType) const;
};

