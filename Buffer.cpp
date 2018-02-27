//
// Created by oleksy on 2/26/2018.
//

#include "Buffer.h"

#include <type_traits>

Buffer::Buffer(Buffer::Type type)
        : type{type} {
    glCreateBuffers(1, &id);
}

Buffer::Buffer(Buffer &&other) noexcept {
    std::swap(id, other.id);
    std::swap(type, other.type);
}

Buffer &Buffer::operator=(Buffer &&other) noexcept {
    std::swap(id, other.id);
    std::swap(type, other.type);
    return *this;
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &id);
}

void Buffer::bind() const {
    glBindBuffer(static_cast<std::underlying_type<Type>::type>(type), id);
}

void Buffer::release() const {
    glBindBuffer(static_cast<std::underlying_type<Type>::type>(type), NoBuffer);
}

GLuint Buffer::getId() const {
    return id;
}