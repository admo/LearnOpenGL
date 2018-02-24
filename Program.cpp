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
    glAttachShader(_id, shader.id());
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
    return glGetUniformLocation(_id, name);
}

GLuint Program::getAttribLocation(const char *name) const {
    const auto location = glGetAttribLocation(_id, name);
    if (location < 0)
        throw std::runtime_error("Error when getting attribute location: " + std::string(name));

    return static_cast<GLuint>(location);
}
