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

    void setUniformValue(GLint location, GLint value) const;
    void setUniformValue(GLint location, GLuint value) const;
    void setUniformValue(GLint location, GLfloat value) const;
    void setUniformValue(GLint location, GLint x, GLint y) const;
    void setUniformValue(GLint location, GLuint x, GLuint y) const;
    void setUniformValue(GLint location, GLfloat x, GLfloat y) const;
    void setUniformValue(GLint location, GLint x, GLint y, GLint z) const;
    void setUniformValue(GLint location, GLuint x, GLuint y, GLuint z) const;
    void setUniformValue(GLint location, GLfloat x, GLfloat y, GLfloat z) const;
    void setUniformValue(GLint location, GLint x, GLint y, GLint z, GLint w) const;
    void setUniformValue(GLint location, GLuint x, GLuint y, GLuint z, GLuint w) const;
    void setUniformValue(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;

private:
    static constexpr GLuint NoProgram{0};
    GLuint _id{NoProgram};
};

