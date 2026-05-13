#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;

enum class LightType {
    Directional,
    Point,
    Spot
};

class Light {
public:
    bool enabled = true;

    static int count;
    int id;

    std::string name;

    glm::vec3 color = glm::vec3(1.0f);
    float intensity = 1.0f;

    const LightType type;

    Light(LightType type);
    Light(LightType type, std::string name);

    virtual void uploadToShader(Shader& shader, int index) = 0;
    virtual void drawGui() = 0;
    virtual ~Light() = default;
};

class DirectionalLight : public Light {
public:
    // for gui use only
    float yaw = -130.0f;
    float pitch = -45.0f;

    glm::vec3 direction;

    DirectionalLight() : Light(LightType::Directional) {}

    void uploadToShader(Shader& shader, int index) override;
    void drawGui() override;
};

class PointLight : public Light {
public:
    glm::vec3 position = glm::vec3(0.0f);
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    PointLight() : Light(LightType::Point) {}

    void uploadToShader(Shader& shader, int index) override;
    void drawGui() override;
};

class SpotLight : public Light {
public:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);
    float innerCutoff = 12.5f;
    float outerCutoff = 17.5f;
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    SpotLight() : Light(LightType::Spot) {}

    void uploadToShader(Shader& shader, int index) override;
    void drawGui() override;
};
