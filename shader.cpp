//
// Created by adamo on 2018-02-11.
//

#include "shader.h"

#include <fstream>
#include <utility>
#include <stdexcept>
#include <vector>

namespace {
template <class T, class... A>
class Call_proxy {
    using pointer_t = T (*)(A...);
    pointer_t p;

public:
    Call_proxy(pointer_t pp): p(pp) {}
    ~Call_proxy() {
        std::cout << "suffix\n";
    }
    T operator()(A&&... args) {
        return p(std::forward<A>(args)...);
    }
};

template <class T, class... A>
class wrap_fn {
    using pointer_t = T (*)(A...);
    pointer_t p;

public:
    wrap_fn(pointer_t pp) : p(pp) {}

    T operator()(A&&... args) {
        std::cout << "prefix\n";
        return Call_proxy<T,A...>(p)(std::forward<A>(args)...);
    }
};

void clearErrors() {
    while (GL_NO_ERROR != glGetError());
}
void checkErrors() {
}
}

class Shader {
public:
    Shader(const char* shaderPath, const GLint shaderType)
    {
        id = createShader(shaderType);

        std::vector<GLchar> shaderCode{readShader(shaderPath)};

        setShaderCode(shaderCode.data(), static_cast<GLint>(shaderCode.size()));
        compileShader();
        checkCompileForErrors();
    }

    Shader(Shader&& rhs) noexcept {
        std::swap(id, rhs.id);
    }

    Shader& operator=(Shader&& rhs) noexcept {
        std::swap(id, rhs.id);

        return *this;
    }

    ~Shader() {
        if (NoShader != id) {
            glDeleteShader(id);
            checkError("glDeleteShader");
        }
    }

    GLuint getId() const {
        if (NoShader == id)
            throw std::runtime_error("");

        return id;
    }

    Shader& operator=(const Shader& rhs) = delete;
    explicit Shader(const Shader&) = delete;

private:
    static constexpr GLuint NoShader = 0;
    GLuint id{NoShader};

    GLuint createShader(GLint shaderType) const {
        const auto id = glCreateShader(shaderType);
        checkError("glCreateShader");

        if (0 == id)
            throw std::runtime_error("");

        return  id;
    }

    void setShaderCode(const GLchar *shaderCode, const GLint size) const {
        glShaderSource(id, 1, &shaderCode, &size);
        checkError("glShaderSource");
    }

    void compileShader() const {
        glCompileShader(id);
        checkError("glCompileShader");
    }

    void checkCompileForErrors() const {
        GLint success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        checkError("glGetShaderiv");

        if (!success) {
            char log[512];
            glGetShaderInfoLog(id, sizeof(log), NULL, log);
            checkError("glGetShaderInfoLog");

            throw std::runtime_error(log);
        }
    }

    void checkError(const char* functionName) const {
        const auto error = glGetError();
        if (GL_NO_ERROR != error)
            throw std::runtime_error(std::string("Error in ") + functionName + " code: " + std::to_string(error));
    }

    std::vector<GLchar> readShader(const char* shaderPath) const {
        std::vector<GLchar> shaderCode;
        std::ifstream shaderFile;

        shaderFile.exceptions(std::ios::failbit | std::ios::badbit);
        shaderFile.open(shaderPath, std::ios::binary);
        shaderFile.seekg(0, std::ios::end);
        const auto size = shaderFile.tellg();
        shaderCode.resize(static_cast<size_t>(size));
        shaderFile.seekg(0, std::ios::beg);
        shaderFile.read(shaderCode.data(), shaderCode.size());

        return shaderCode;
    }
};

Program::Program(const char *vertexPath, const char *fragmentPath) {
    const Shader vertexShader{vertexPath, GL_VERTEX_SHADER};
    const Shader fragmentShader{fragmentPath, GL_FRAGMENT_SHADER};

    int success;
    id = glCreateProgram();
    glAttachShader(id, vertexShader.getId());
    glAttachShader(id, fragmentShader.getId());
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(id, sizeof(infoLog), NULL, infoLog);
//        std::clog << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
    }
}