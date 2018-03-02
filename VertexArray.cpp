//
// Created by adamo on 2018-02-26.
//

#include "VertexArray.h"

#include <utility>

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id);
}

VertexArray::VertexArray(VertexArray &&other) noexcept {
    std::swap(id, other.id);
}

VertexArray &VertexArray::operator=(VertexArray &&other) noexcept {
    std::swap(id, other.id);
    return *this;
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id);
}

void VertexArray::bind() const {
    glBindVertexArray(id);
}

void VertexArray::release() const {
    glBindVertexArray(NoVertexArray);
}
