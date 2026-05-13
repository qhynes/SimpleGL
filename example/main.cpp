
// headers for OpenGL
#include "glad/glad.h"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// include all of SimpleGL
#include <SimpleGL/SimpleGL.h>

// other C++ libraries
#include <iostream>
#include <vector>

int main() {
    
    Window window("SimpleGL", 800, 600);
    Input input;
    Timer timer;

    if (window.init() != 0) {
        std::cerr << "Init failed \n";
        return 1;
    }

    Vertex vertices[] = {
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    };

    uint32_t indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    std::vector<Vertex> v(std::begin(vertices), std::end(vertices));
    std::vector<uint32_t> i(std::begin(indices), std::end(indices));

    Mesh quad(v, i);
    Shader shader("shaders/shader.vert", "shaders/shader.frag");
    Texture texture("assets/container.jpg");
    Material material;
    material.shader = &shader;
    material.diffuse = &texture;

    Camera camera;
    Renderer renderer;

    glm::mat4 model = glm::mat4(1.0f);

    while (window.isOpen()) {
        float dt = timer.tick();
        dt = std::min(dt, 0.033f);

        input.beginFrame();
        window.pollEvents(input);

        camera.update(input, dt);

        renderer.beginFrame(camera, window);

        renderer.draw(quad, material, model);

        window.swapBuffers();
    }

    window.cleanup();

    return 0;
}
