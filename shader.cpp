//
// Created by adamo on 2018-02-11.
//

#include "shader.h"

#include <fstream>
#include <utility>
#include <stdexcept>
#include <vector>

namespace {
template <class T, class... Ts>
decltype(auto) wrap_opengl(T fun, Ts&&... args) {
    struct guard_t {
        ~guard_t() noexcept(false) {
            const auto& error = glGetError();
            if (GL_NO_ERROR != error) throw std::runtime_error(std::string("Error in OpenGL: ") + std::to_string(error));
        }
    } guard;

    while (GL_NO_ERROR != glGetError());
    return fun(std::forward<Ts>(args)...);
};
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

    ~Shader() noexcept {
        wrap_opengl(glDeleteShader, id); // 0 is silently ignored by this function
    }

    GLuint get() const noexcept {
        return id;
    }

    Shader& operator=(const Shader& rhs) = delete;
    explicit Shader(const Shader&) = delete;

private:
    static constexpr GLuint NoShader = 0;
    GLuint id{NoShader};

    GLuint createShader(GLint shaderType) const {
        const auto id = wrap_opengl(glCreateShader, shaderType);

        if (NoShader == id)
            throw std::runtime_error("");

        return  id;
    }

    void setShaderCode(const GLchar *shaderCode, const GLint size) const {
        wrap_opengl(glShaderSource, id, 1, &shaderCode, &size);
    }

    void compileShader() const {
        wrap_opengl(glCompileShader, id);
    }

    void checkCompileForErrors() const {
        GLint success;
        wrap_opengl(glGetShaderiv, id, GL_COMPILE_STATUS, &success);

        if (!success) {
            char log[512];
            wrap_opengl(glGetShaderInfoLog, id, sizeof(log), nullptr, log);

            throw std::runtime_error(log);
        }
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
    id = wrap_opengl(glCreateProgram);
    wrap_opengl(glAttachShader, id, vertexShader.get());
    wrap_opengl(glAttachShader, id, fragmentShader.get());
    wrap_opengl(glLinkProgram, id);
    wrap_opengl(glGetProgramiv, id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        wrap_opengl(glGetProgramInfoLog, id, sizeof(infoLog), nullptr, infoLog);
//        std::clog << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
    }
}

void Program::use() {
    wrap_opengl(glUseProgram, id);
}

Program::~Program() {
    glDeleteProgram(id); // 0 is silently ignored by this function
}
