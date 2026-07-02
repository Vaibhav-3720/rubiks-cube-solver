cmake_minimum_required(VERSION 3.16)

project(
    RubiksCubeSolver
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# ---------------------------------------------------------------------------
# Shared library: cube models, solvers, pattern databases (everything under
# src/ except the two executable entry points).
# ---------------------------------------------------------------------------
file(GLOB_RECURSE LIB_SOURCES
    src/Model/*.cpp
    src/Solver/*.cpp
    src/PatternDatabases/*.cpp
)

add_library(rubiks_cube_lib STATIC
    ${LIB_SOURCES}
)

target_include_directories(rubiks_cube_lib PUBLIC
    include
)

if(MSVC)
    target_compile_options(rubiks_cube_lib PUBLIC /W4)
else()
    target_compile_options(rubiks_cube_lib PUBLIC
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# ---------------------------------------------------------------------------
# Main solver / benchmark executable
# ---------------------------------------------------------------------------
add_executable(RubiksCubeSolver
    src/main.cpp
)

target_link_libraries(RubiksCubeSolver PRIVATE
    rubiks_cube_lib
)

# ---------------------------------------------------------------------------
# Standalone tool to (re)generate the corner pattern database
# ---------------------------------------------------------------------------
add_executable(generate_corner_db
    tools/generate_corner_db.cpp
)

target_link_libraries(generate_corner_db PRIVATE
    rubiks_cube_lib
)
