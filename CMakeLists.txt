cmake_minimum_required(VERSION 3.20)
project(SimpleGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)

add_library(SimpleGL
    src/buffers.cpp
    src/camera.cpp
    src/editor.cpp
    src/light.cpp
    src/mesh.cpp
    src/object.cpp
    src/primitives.cpp
    src/renderer.cpp
    src/scene.cpp
    src/shader.cpp
    src/texture.cpp
    src/transform.cpp
    src/window.cpp

    external/glad/src/glad.c

    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/backends/imgui_impl_sdl2.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(SimpleGL
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/backends
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/external/stb
)

target_link_libraries(SimpleGL
    PUBLIC
        SDL2::SDL2
        glm::glm
)

target_compile_features(SimpleGL PUBLIC cxx_std_20)

add_executable(sandbox
    sandbox/main.cpp
)

target_link_libraries(sandbox
    PRIVATE
        SimpleGL
)

target_compile_definitions(sandbox
    PRIVATE
        SIMPLEGL_ASSET_DIR="${CMAKE_SOURCE_DIR}/sandbox/assets/"
        SIMPLEGL_SHADER_DIR="${CMAKE_SOURCE_DIR}/sandbox/shaders/"
)
