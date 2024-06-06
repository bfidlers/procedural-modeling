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

# Find GLPK library
set(GLPK_INCLUDE_DIRS /opt/homebrew/include)
set(GLPK_LIBRARIES /opt/homebrew/lib/libglpk.dylib)

add_library(ProcMod_lib OBJECT
    CameraTrackball.cpp
    Input.cpp
    Point.cpp
    Face.cpp
    EdgeLabel.cpp
    InputEdge.cpp
    Primitive.cpp
    InputVertex.cpp
    InputGraph.cpp
    GraphBoundary.cpp
    LinearEquationSolver.cpp
    Graph.cpp
    Util.cpp
    GraphIsomorphism.cpp
)

include_directories("../third-party/")

target_include_directories(ProcMod_lib PUBLIC .)

add_executable(ProceduralModeling main.cpp)
target_link_libraries(ProceduralModeling PUBLIC ProcMod_lib OpenGL::GL OpenGL::GLU GLUT::GLUT)

# Include GLPK directories
target_include_directories(ProceduralModeling PRIVATE ${GLPK_INCLUDE_DIRS})

# Link GLPK libraries
target_link_libraries(ProceduralModeling PRIVATE ${GLPK_LIBRARIES})
