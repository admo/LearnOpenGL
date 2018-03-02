//
// Created by adamo on 2018-02-26.
//

#pragma once

#include "glad/glad.h"

class VertexArray {
public:
    VertexArray();
    VertexArray(VertexArray&& other) noexcept;
    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(VertexArray&& other) noexcept;
    VertexArray& operator=(const VertexArray&) = delete;
    ~VertexArray();

    void bind() const;
    void release() const;

private:
    static constexpr GLuint NoVertexArray = 0;
    GLuint id{NoVertexArray};
};

