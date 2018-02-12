//
// Created by adamo on 2018-02-11.
//

#include "shader.h"

#include <fstream>
#include <functional>
#include <memory>
#include <iostream>
#include <utility>

namespace {
template <class T, class D>
class Handler {
public:
    Handler()
            : _t(T(), D())
    {}

    Handler(T t)
            : _t(t, D())
    {}

    Handler(Handler&& h)
            : _t(h.release(), std::forward<D>(h.get_deleter()))
    {
    }

    ~Handler() {
        D(t);
    }

    T release() {
        return std::get<0>(_t);
    }

    D get_deleter() {
        return std::get<1>(_t);
    }

private:
    std::tuple<T, D> _t;
};

void foo(int*);

using ShaderHandler = Handler<int, void(*)(int*)>;

//using Dupa = Handler<int, &foo>;
//using Blada = Handler<int, std::function<void(int)>(foo)>;
}

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {
    const auto vertexShader = compileShader(readShader(vertexPath).c_str(), GL_VERTEX_SHADER);
    const auto fragmentShader = compileShader(readShader(fragmentPath).c_str(), GL_FRAGMENT_SHADER);

    int success;
    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(id, sizeof(infoLog), NULL, infoLog);
        std::clog << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

int Shader::compileShader(const char *shaderCode, int shaderType) const {
    unsigned int shaderId;
    int success;
    shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &shaderCode, NULL);
    glCompileShader(shaderId);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderId, sizeof(infoLog), NULL, infoLog);
        std::clog << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << "\n";
    }

    return shaderId;
}

std::string Shader::readShader(const GLchar *path) const {
    std::string shaderCode;
    std::ifstream shaderFile;

    shaderFile.exceptions(std::ios::failbit | std::ios::badbit);
    shaderFile.open(path, std::ios::binary);
    shaderFile.seekg(0, std::ios::end);
    const auto size = shaderFile.tellg();
    shaderCode.resize(static_cast<size_t>(size));
    shaderFile.seekg(0, std::ios::beg);
    shaderFile.read(&shaderCode[0], shaderCode.size());

    return shaderCode;
}
