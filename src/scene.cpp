#include <SimpleGL/scene.h>

#include <SimpleGL/camera.h>
#include <SimpleGL/object.h>

Scene::Scene(const Window& window, Camera& camera) : camera(camera) {
    projection = glm::perspective(
        glm::radians(camera.getFov()),
        window.getAspectRatio(),
        0.1f,
        1000.0f
    );
}

void Scene::addObject(std::unique_ptr<Object> object) {
    objects.push_back(std::move(object));
}

void Scene::addLight(std::unique_ptr<Light> light) {
    lights.push_back(std::move(light));
}