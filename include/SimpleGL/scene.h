#pragma once

#include <SimpleGL/light.h>
#include <SimpleGL/object.h>
#include <SimpleGL/window.h>

#include <memory>
#include <vector>

class Camera;
class Light;
class Object;

class Scene {
public:
    // renderer settings
    glm::vec3 backgroundColor = glm::vec3(0.08f, 0.10f, 0.13f);
    glm::vec3 ambientColor = glm::vec3(1.0f);
    float ambientStrength = 0.2f;

    glm::mat4 projection;

    Camera& camera;
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<Light>> lights;

    Scene(const Window& window, Camera& camera);

    void addObject(std::unique_ptr<Object> object);
    void addLight(std::unique_ptr<Light> light);

    void drawGui();
};
