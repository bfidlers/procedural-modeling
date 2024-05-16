cmake_minimum_required(VERSION 3.20)

project(ProceduralModeling)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Suppress warnings of the deprecation of glut functions on macOS.
if(APPLE)
  add_definitions(-Wno-deprecated-declarations)
endif()

# Find dependencies.
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_library(ProcMod_lib OBJECT
    CameraTrackball.cpp
    Input.cpp
    Point.cpp
    Face.cpp
    EdgeLabel.cpp
    Edge.cpp
    Primitive.cpp
    Vertex.cpp
    Graph.cpp
    GraphBoundary.cpp
)

include_directories("../third-party/")

target_include_directories(ProcMod_lib PUBLIC .)

add_executable(ProceduralModeling main.cpp)
target_link_libraries(ProceduralModeling PUBLIC ProcMod_lib OpenGL::GL OpenGL::GLU GLUT::GLUT)
