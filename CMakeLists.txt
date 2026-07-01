cmake_minimum_required(VERSION 3.16)

project(
    RubiksCubeSolver
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(RubiksCubeSolver
    ./RubiksCubeSolver
    ${SOURCES}
)

target_include_directories(RubiksCubeSolver PRIVATE
    include
)

if(MSVC)
    target_compile_options(RubiksCubeSolver PRIVATE /W4)
else()
    target_compile_options(RubiksCubeSolver PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()