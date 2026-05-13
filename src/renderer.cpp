#include <SimpleGL/renderer.h>

#include <SimpleGL/camera.h>
#include <SimpleGL/light.h>
#include <SimpleGL/material.h>
#include <SimpleGL/mesh.h>
#include <SimpleGL/object.h>
#include <SimpleGL/scene.h>
#include <SimpleGL/shader.h>
#include <SimpleGL/texture.h>
#include <SimpleGL/window.h>

#include "glad/glad.h"

#include <stdio.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/string_cast.hpp>

Renderer::Renderer() {
    // renderer settings
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_FRAMEBUFFER_SRGB);
}

void Renderer::uploadCamera(const Camera& camera, Shader& shader) {
    shader.setMat4("view", camera.getViewMatrix());
    shader.setVec3("viewPos", camera.position);
}

void Renderer::uploadLights(const std::vector<std::unique_ptr<Light>>& lights, Shader& shader) {
    bool hasDirLight = false;
    int pointIndex = 0;
    int spotIndex = 0;

    for (int i = 0; i < lights.size(); i++) {
        if (!lights[i]->enabled) continue;
        
        switch (lights[i]->type) {
            case LightType::Directional:
                lights[i]->uploadToShader(shader, 0);
                hasDirLight = true;
                break;
            case LightType::Point:
                lights[i]->uploadToShader(shader, pointIndex);
                pointIndex++;
                break;
            case LightType::Spot:
                lights[i]->uploadToShader(shader, spotIndex);
                spotIndex++;
                break;
        }
    }

    shader.setBool("hasDirLight", hasDirLight);
    shader.setInt("numPointLights", pointIndex);
    shader.setBool("numSpotLights", spotIndex);
}

void Renderer::render(const Scene& scene) {
    glClearColor(
        scene.backgroundColor.r,
        scene.backgroundColor.g,
        scene.backgroundColor.b,
        1.0f
    );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Camera& camera = scene.camera;

    for (const auto& object : scene.objects) {
        if (!object->enabled || !object->mesh || !object->material) continue;

        Shader& shader = object->material->shader;

        shader.use();

        object->material->bind();

        glm::mat4 view = camera.getViewMatrix();

        shader.setMat4("view", view);
        shader.setVec3("viewPos", glm::vec3(0.0f, 0.0f, 3.0f));

        // uploadCamera(scene.camera, shader);
        uploadLights(scene.lights, shader);

        shader.setMat4("projection", scene.projection);

        shader.setVec3("ambientColor", scene.ambientColor);
        shader.setFloat("ambientStrength", scene.ambientStrength);

        glm::mat4 model = object->transform.getMatrix();
        shader.setMat4("model", model);

        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
        shader.setMat3("normalMatrix", normalMatrix);

        // std::cout << "Drawing...\n";
        object->mesh->draw();
    }
}
