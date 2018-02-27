//
// Created by adamo on 2018-02-21.
//

#include <utility>
#include <stdexcept>
#include "Program.h"
#include "Shader.h"

Program::Program()
        : _id(glCreateProgram()) {}

Program::Program(Program &&other) noexcept {
    std::swap(_id, other._id);
}

Program &Program::operator=(Program &&other) noexcept {
    std::swap(_id, other._id);
    return *this;
}

Program::~Program() {
    glDeleteProgram(_id);
}

bool Program::attachShader(const Shader &shader) const {
    // When Shader is attached, then it can be safely deleted by glDeleteShader.
    // In such case Shader will exist until Program exists.
    glAttachShader(_id, shader.getId());
    return true;
}

bool Program::link() const {
    glLinkProgram(_id);
    return true;
}

void Program::bind() const {
    glUseProgram(_id);
}

GLint Program::getUniformLocation(const char *name) const {
    const auto location = glGetUniformLocation(_id, name);
    if (location < 0)
        throw std::runtime_error("Error when getting uniform location: " + std::string(name));

    return location;
}

GLuint Program::getAttribLocation(const char *name) const {
    const auto location = glGetAttribLocation(_id, name);
    if (location < 0)
        throw std::runtime_error("Error when getting attribute location: " + std::string(name));

    return static_cast<GLuint>(location);
}

void Program::setUniformValue(GLint location, GLint value) const {
    glUniform1i(location, value);
}

void Program::setUniformValue(GLint location, GLuint value) const {
    glUniform1ui(location, value);
}

void Program::setUniformValue(GLint location, GLfloat value) const {
    glUniform1f(location, value);
}

void Program::setUniformValue(GLint location, GLint x, GLint y) const {
    glUniform2i(location, x, y);
}

void Program::setUniformValue(GLint location, GLuint x, GLuint y) const {
    glUniform2ui(location, x, y);
}

void Program::setUniformValue(GLint location, GLfloat x, GLfloat y) const {
    glUniform2f(location, x, y);
}

void Program::setUniformValue(GLint location, GLint x, GLint y, GLint z) const {
    glUniform3i(location, x, y, z);
}

void Program::setUniformValue(GLint location, GLuint x, GLuint y, GLuint z) const {
    glUniform3ui(location, x, y, z);
}

void Program::setUniformValue(GLint location, GLfloat x, GLfloat y, GLfloat z) const {
    glUniform3f(location, x, y, z);
}

void Program::setUniformValue(GLint location, GLint x, GLint y, GLint z, GLint w) const {
    glUniform4i(location, x, y, z, w);
}

void Program::setUniformValue(GLint location, GLuint x, GLuint y, GLuint z, GLuint w) const {
    glUniform4ui(location, x, y, z, w);
}

void Program::setUniformValue(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const {
    glUniform4f(location, x, y, z, w);
}
