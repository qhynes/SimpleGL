#pragma once

#include <SimpleGL/light.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Camera;
class Light;
class Material;
class Mesh;
class Object;
class Scene;
class Shader;
class Texture;
class Window;

class Renderer {
public:
    Renderer();

    void render(const Scene& scene);

    void uploadCamera(const Camera& camera, Shader& shader);
    void uploadLights(const std::vector<std::unique_ptr<Light>>& lights, Shader& shader);
};