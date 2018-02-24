//
// Created by adamo on 2018-02-11.
//

#pragma once

#include <tuple>

#include <glad/glad.h>

class Shader {
public:
    enum class Type: GLenum {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        Geometry = GL_GEOMETRY_SHADER
    };

    explicit Shader(Type type);
    Shader(Type type, const char* filename);
    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;
    Shader& operator=(const Shader& rhs) = delete;
    explicit Shader(const Shader&) = delete;
    ~Shader();

    void compileSourceFile(const char *filename);
    GLuint id() const;

private:
    static constexpr GLuint NoShader = 0;
    std::tuple<GLuint, Type> data{NoShader, Type::Vertex};

    void setShaderCode(const GLchar *shaderCode, GLint size) const;
    void compileShader() const;
    void checkCompileForErrors() const;
};