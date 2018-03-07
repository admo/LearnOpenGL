#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Program.h"
#include "Buffer.h"
#include "VertexArray.h"
#include <iostream>

namespace {
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

std::vector<float> vertices = {
        0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f
};

std::vector<unsigned int> indices = {
        0, 1, 3,
        1, 2, 3
};
}

int main() try {
    // glfw: initialize and configure
    // ------------------------------
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    {
        // glfw window creation
        // --------------------
        GLFWwindow *window = glfwCreateWindow(800, 800, "LearnOpenGL", nullptr, nullptr);
        if (nullptr == window) {
            std::cout << "Failed to create GLFW window\n";
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD\n";
            return -1;
        }

        Program program;
        program.attachShader({Shader::Type::Vertex, "../shader.vert"});
        program.attachShader({Shader::Type::Fragment, "../shader.frag"});
        program.link();

        const auto vertexIndex = program.getAttribLocation("vertexPosition");
//        const auto colorIndex = program.getAttribLocation("vertexColor");

        Buffer vbo(Buffer::Type::Vertex, vertices);
        Buffer ebo(Buffer::Type::Index, indices);

        VertexArray vao;
        vao.bind();

        glBindVertexBuffer(vertexIndex, vbo.getId(), 0, 5*sizeof(float)); // version without binding vao is glVertexArrayVertexBuffer
        glVertexAttribFormat(vertexIndex, 2, GL_FLOAT, GL_FALSE, 0); // version without binding vao is glVertexArrayAttribFormat
        glVertexAttribBinding(vertexIndex, vertexIndex); // version without binding vao is glVertexArrayAttribBinding
        glEnableVertexAttribArray(vertexIndex); // version without binding vao is glEnableVertexArrayAttrib

//        glBindVertexBuffer(colorIndex, vbo.getId(), vertices.data(), 5*sizeof(float)); // version without binding vao is glVertexArrayAttribFormat
//        glEnableVertexAttribArray(colorIndex); // version without binding vao is glVertexArrayVertexBuffer glEnableVertexArrayAttrib
//        glVertexAttribFormat(colorIndex, 2, GL_FLOAT, GL_FALSE, 0); // version without binding vao is glVertexArrayVertexBuffer

//        vbo.bind();
        ebo.bind();

//        glVertexAttribPointer(vertexIndex, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
//        glEnableVertexAttribArray(vertexIndex);

//        glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (2 * sizeof(float)));
//        glEnableVertexAttribArray(colorIndex);

        // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        vao.release();

        // uncomment this call to draw in wireframe polygons.
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//        const auto vertexColorLocation = program.getUniformLocation("ourColor");
        program.bind();
        vao.bind();

        // render loop
        while (!glfwWindowShouldClose(window)) {
            // input
            // -----
            processInput(window);

            // render
            // ------
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // draw our first triangle
//            const auto timeValue = glfwGetTime();
//            const auto greenValue = static_cast<GLfloat>((std::sin(timeValue) / 2.0f) + 0.5f);

//            program.setUniformValue(vertexColorLocation, greenValue);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            // check and call events and swap the buffers
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
catch (std::exception& e) {
    std::clog << "Exception: " << e.what();
}

namespace {
void framebuffer_size_callback(GLFWwindow */*window*/, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

}