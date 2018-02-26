//
// Created by oleksy on 2/26/2018.
//

#include "Buffer.h"

#include <type_traits>

Buffer::Buffer(Buffer::Type type)
        : data{NoBuffer, type}
{
    glGenBuffers(1, &std::get<0>(data));
}

Buffer::Buffer(Buffer &&other) noexcept {
    data.swap(other.data);
}

Buffer &Buffer::operator=(Buffer &&other) noexcept {
    data.swap(other.data);
    return *this;
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &std::get<0>(data));
}

void Buffer::bind() const {
    glBindBuffer(static_cast<std::underlying_type<Type>::type>(std::get<1>(data)), std::get<0>(data));
}

void Buffer::release() const {
    glBindBuffer(static_cast<std::underlying_type<Type>::type>(std::get<1>(data)), NoBuffer);
}

GLuint Buffer::getId() const {
    return std::get<0>(data);
}