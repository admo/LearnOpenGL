//
// Created by adamo on 2018-02-21.
//

#pragma once
#include <glad/glad.h>

class Shader;

class Program {
public:
    Program();
    Program(Program&& other) noexcept;
    Program(const Program&) = delete;
    Program& operator=(const Program&) = delete;
    Program& operator=(Program&& other) noexcept;

    ~Program();

    bool attachShader(const Shader &shader) const;
    GLint getUniformLocation(const char* name) const;
    GLuint getAttribLocation(const char *name) const;
    bool link() const;
    void bind() const;

private:
    static constexpr GLuint NoProgram{0};
    GLuint _id{NoProgram};
};

