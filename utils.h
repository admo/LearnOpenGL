//
// Created by adamo on 2018-02-21.
//

#pragma once

#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <glad/glad.h>

std::vector<GLchar> read_file(const char *file_name);

//template <class Function, class... Args>
//decltype(auto) wrap_glCheckErrors(Function f, const char* err_msg, Args &&... args) {
//    struct guard_t {
//        const char* err_msg;
//        explicit guard_t(const char* err_msg) : err_msg(err_msg) {}
//        ~guard_t() noexcept(false) {
//            const auto& error = glGetError();
//            if (GL_NO_ERROR != error)
//                throw std::runtime_error(std::string("Error code: ") + std::to_string(error) + " when calling " + err_msg);
//        }
//    } guard(err_msg);
//
//    while (GL_NO_ERROR != glGetError());
//    return f(std::forward<Args>(args)...);
//};
//
//#define STRINGIFICATOR(X) #X
//#define GLCHECKERRORS(f, ...) wrap_glCheckErrors(f, #f " in " __FILE__ ":" STRINGIFICATOR(__LINE__), ##__VA_ARGS__)