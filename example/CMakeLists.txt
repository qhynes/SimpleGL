# CMakeLists.txt file for a project using SimpleGL

cmake_minimum_required(VERSION 3.20)
project(ProjectName LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# reference SimpleGL directly
add_subdirectory(
    ../SimpleGL
    ${CMAKE_BINARY_DIR}/SimpleGL
)

# or include entire SimpleGL library (as a symlink)
add_subdirectory(external/SimpleGL)

add_executable(ProjectName
    src/main.cpp
)

target_link_libraries(ProjectName PRIVATE SimpleGL)
