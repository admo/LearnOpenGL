//
// Created by adamo on 2018-02-24.
//

#include "utils.h"

#include <fstream>

std::vector<GLchar> read_file(const char *file_name) {
    std::vector<GLchar> data;
    std::ifstream file_stream;

    file_stream.exceptions(std::ios::failbit | std::ios::badbit);
    file_stream.open(file_name, std::ios::binary);
    file_stream.seekg(0, std::ios::end);
    const auto size = file_stream.tellg();
    data.resize(static_cast<size_t>(size));
    file_stream.seekg(0, std::ios::beg);
    file_stream.read(data.data(), data.size());

    return data;
}