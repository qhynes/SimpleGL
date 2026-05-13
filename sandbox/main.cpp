
#include <SimpleGL/SimpleGL.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

// other C++ libraries
#include <iostream>
#include <string>
#include <vector>

std::string assetPath(const std::string& filename) {
    return std::string(SIMPLEGL_ASSET_DIR) + filename;
}

glm::vec3 srgbToLinear(glm::vec3 c) {
    return glm::pow(c, glm::vec3(2.2f));
}

int main() {
    
    Window window("Simple GL", 800, 600);
    Input input;
    Timer timer;

    if (!window.init()) {
        std::cerr << "Init failed \n";
        return 1;
    }

    Camera camera;

    Scene scene(window, camera);
    scene.backgroundColor = srgbToLinear(glm::vec3(0.53, 0.81, 0.98));

    Renderer renderer;

    MeshData cubeData = Primitives::cube();
    MeshData sphereData = Primitives::uv_sphere(10, 10);
    MeshData gridData = Primitives::grid(1.0f, 1.0f, 10, 10, false);
    Mesh cube(cubeData.vertices, cubeData.indices);
    Mesh sphere(sphereData.vertices, sphereData.indices);
    Mesh grid(gridData.vertices, gridData.indices);

    Shader lightShader(
        std::string(SIMPLEGL_SHADER_DIR) + "multi_light.vert",
        std::string(SIMPLEGL_SHADER_DIR) + "multi_light.frag"
    );

    Shader flatShader(
        std::string(SIMPLEGL_SHADER_DIR) + "flat.vert",
        std::string(SIMPLEGL_SHADER_DIR) + "flat.frag"
    );
    
    Texture yellow(255, 255, 0, 255);
    Texture black(0, 0, 0, 255);

    Texture uvChecker(std::string(SIMPLEGL_ASSET_DIR) + "UVChecker.png", true);

    Texture brick_diffuse(std::string(SIMPLEGL_ASSET_DIR) + "brick/diffuse.png", true);
    Texture brick_specular(std::string(SIMPLEGL_ASSET_DIR) + "brick/specular.png", false);

    Texture container_diffuse(std::string(SIMPLEGL_ASSET_DIR) + "container/diffuse.png", true);
    Texture container_specular(std::string(SIMPLEGL_ASSET_DIR) + "container/specular.png", false);

    Texture metal_diffuse(std::string(SIMPLEGL_ASSET_DIR) + "metal/diffuse.png", true);
    Texture metal_specular(std::string(SIMPLEGL_ASSET_DIR) + "metal/specular.png", false);

    Texture terrain_diffuse(std::string(SIMPLEGL_ASSET_DIR) + "terrain/diffuse.png", true);
    Texture terrain_specular(std::string(SIMPLEGL_ASSET_DIR) + "terrain/specular.png", false);

    Texture wood_diffuse(std::string(SIMPLEGL_ASSET_DIR) + "wood/diffuse.png", true);
    Texture wood_specular(std::string(SIMPLEGL_ASSET_DIR) + "wood/specular.png", false);

    Material flatYellow(flatShader, yellow, black);
    Material uvCheck(lightShader, uvChecker, black);
    Material brick(lightShader, brick_diffuse, brick_specular);
    Material container(lightShader, container_diffuse, container_specular);
    Material metal(lightShader, metal_diffuse, metal_specular);
    Material terrain(lightShader, terrain_diffuse, black);
    Material wood(lightShader, wood_diffuse, wood_specular);
    
    DirectionalLight sunRays;
    sunRays.direction = glm::normalize(glm::vec3(-0.5f, -0.5f, -0.3f));
    float sunDistance = 50.0f;
    scene.addLight(std::make_unique<DirectionalLight>(sunRays));

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // scene
    Object groundPlane;
    groundPlane.mesh = &grid;
    groundPlane.material = &terrain;
    scene.addObject(std::make_unique<Object>(groundPlane));

    int numBoxes = 3;
    Object boxes[numBoxes];
    for (int i = 0; i < numBoxes; i++) {
        boxes[i].mesh = &cube;
        boxes[i].material = &wood;
        scene.addObject(std::make_unique<Object>(boxes[i]));
    }

    Object sun;
    sun.mesh = &sphere;
    sun.material = &flatYellow;
    scene.addObject(std::make_unique<Object>(sun));

    EditorGui editor;

    while (window.isOpen()) {
        float dt = timer.tick();
        dt = std::min(dt, 0.033f);

        input.beginFrame();
        window.pollEvents(input);

        if (SDL_GetRelativeMouseMode() == SDL_TRUE) {
            camera.update(input, dt);
        }

        sun.transform.position = camera.position - sunDistance * sunRays.direction;

        renderer.render(scene);

        // create gui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();

        editor.draw(scene);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window.swapBuffers();
    }

    window.cleanup();

    return 0;
}
