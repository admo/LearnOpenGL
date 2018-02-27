cmake_minimum_required(VERSION 3.8)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)

# GLFW settings
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

include_directories(${CMAKE_SOURCE_DIR}/glad/include)
include_directories(${CMAKE_SOURCE_DIR}/glfw/include)

set(SOURCE_FILES main.cpp glad/src/glad.c Shader.cpp Shader.h Program.cpp Program.h utils.h utils.cpp Buffer.cpp Buffer.h VertexArray.cpp VertexArray.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} glfw)