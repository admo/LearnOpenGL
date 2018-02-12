//
// Created by adamo on 2018-02-11.
//

#include <glad/glad.h>
#include <string>

#pragma once

class Program {
public:
    unsigned int id;

    Program(const char *vertexPath, const char *fragmentPath);

    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float) const;
};

