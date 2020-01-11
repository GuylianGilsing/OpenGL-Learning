cmake_minimum_required (VERSION 3.8)

project(OpenGL-Learning)

include_directories(./dependencies/GLFW/include)
include_directories(./dependencies/GLAD/include)
link_directories(./dependencies/GLFW/lib-vc-2019)

find_package(OpenGL REQUIRED)
add_executable(App "./src/main.cpp")
target_link_libraries(App opengl32 glfw32)

add_subdirectory(./dependencies/GLAD/src)