//
// Created by adamo on 2018-02-11.
//

#include "Shader.h"
#include <type_traits>
#include <stdexcept>
#include <iostream>
#include "utils.h"

Shader::Shader(Shader::Type type)
        : id{glCreateShader(static_cast<std::underlying_type<Type>::type>(type))}
        , type{type} {}

Shader::Shader(Shader::Type type, const char *filename)
        : Shader{type} {
    compileSourceFile(filename);
}

Shader::Shader(Shader &&other) noexcept {
    std::swap(id, other.id);
    std::swap(type, other.type);
}

Shader &Shader::operator=(Shader &&other) noexcept {
    std::swap(id, other.id);
    std::swap(type, other.type);
    return *this;
}

Shader::~Shader() {
    glDeleteShader(id);
}

void Shader::compileSourceFile(const char *filename) {
    std::vector<GLchar> shaderCode{read_file(filename)};
    setShaderCode(shaderCode.data(), static_cast<GLint>(shaderCode.size()));
    compileShader();
    checkCompileForErrors();
}

void Shader::setShaderCode(const GLchar *shaderCode, const GLint size) const {
    glShaderSource(id, 1, &shaderCode, &size);
}

void Shader::compileShader() const {
    glCompileShader(id);
}

void Shader::checkCompileForErrors() const {
    GLint success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

   if (success != GL_TRUE) {
       char info[1024];
       glGetShaderInfoLog(id, 1024, nullptr, info);
       std::clog << info << '\n';
       throw std::runtime_error("Error when compiling shader");
   }
}

GLuint Shader::getId() const {
    return id;
}
