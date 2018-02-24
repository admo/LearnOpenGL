//
// Created by adamo on 2018-02-11.
//

#include "Shader.h"
#include <type_traits>
#include <stdexcept>
#include "utils.h"

Shader::Shader(Shader::Type type)
        : data{glCreateShader(static_cast<std::underlying_type<Type>::type>(type)), type} {}

Shader::Shader(Shader::Type type, const char *filename)
        : Shader{type} {
    compileSourceFile(filename);
}

Shader::Shader(Shader &&other) noexcept {
    data.swap(other.data);
}

Shader &Shader::operator=(Shader &&other) noexcept {
    data.swap(other.data);
    return *this;
}

Shader::~Shader() {
    glDeleteShader(std::get<0>(data));
}

void Shader::compileSourceFile(const char *filename) {
    std::vector<GLchar> shaderCode{read_file(filename)};
    setShaderCode(shaderCode.data(), static_cast<GLint>(shaderCode.size()));
    compileShader();
    checkCompileForErrors();
}

void Shader::setShaderCode(const GLchar *shaderCode, const GLint size) const {
    glShaderSource(std::get<0>(data), 1, &shaderCode, &size);
}

void Shader::compileShader() const {
    glCompileShader(std::get<0>(data));
}

void Shader::checkCompileForErrors() const {
    GLint success;
    glGetShaderiv(std::get<0>(data), GL_COMPILE_STATUS, &success);

   if (success != GL_TRUE)
       throw std::runtime_error("Error when compiling shader");
}

GLuint Shader::id() const {
    return std::get<0>(data);
}
