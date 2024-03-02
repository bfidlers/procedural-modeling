cmake_minimum_required(VERSION 3.20)

project(ProceduralModeling)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_library(ProcMod_lib OBJECT
    input.cpp
)

target_include_directories(ProcMod_lib PUBLIC .)

add_executable(ProceduralModeling main.cpp)
target_link_libraries(ProceduralModeling PUBLIC ProcMod_lib)
