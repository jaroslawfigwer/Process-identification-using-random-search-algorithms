cmake_minimum_required(VERSION 3.10)

project(Example)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(sources ${sources} 
    Example.cpp
    src/Master.cpp
    src/Result.cpp
    src/Worker.cpp
)

# add the executable
add_executable(Example ${sources})