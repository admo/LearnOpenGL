//
// Created by oleksy on 2/26/2018.
//

#pragma once

#include "glad/glad.h"

#include <tuple>
#include <vector>

class Buffer {
public:
    enum class Type: GLenum {
        Vertex = GL_ARRAY_BUFFER,
        Index = GL_ELEMENT_ARRAY_BUFFER
    };

    explicit Buffer(Type type);
    Buffer(Buffer&& other) noexcept;
    explicit Buffer(const Buffer&) = delete;
    Buffer& operator=(Buffer&& other) noexcept;
    Buffer& operator=(const Buffer&) = delete;
    ~Buffer();

    void bind() const;
    void release() const;
    GLuint getId() const;

    template <class T>
    void copy(const std::vector<T> &d) const {
        glNamedBufferData(std::get<0>(data), d.size()*sizeof(T), d.data(), GL_STATIC_DRAW);
    }


private:
    static constexpr GLuint NoBuffer{0};
    std::tuple<GLuint, Type> data{NoBuffer, Type::Vertex};
};
