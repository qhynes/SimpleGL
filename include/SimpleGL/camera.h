#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Input;

class Camera {
public:
    Camera(
        glm::vec3 position = glm::vec3(0.0f, 3.0f, 3.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
        float yaw = -90.0f,
        float pitch = 0.0f
    );

    void update(const Input& input, float dt);
    glm::mat4 getViewMatrix() const;
    glm::vec3 getPosition() const;
    float getFov() const;

// private:
    void recalculateVectors();
    bool hasChanged = true;

    // camera settings
    float speed = 5.0f;
    float sensitivity = 0.2f;
    float yaw;
    float pitch;
    float fov = 45.0f;

    // camera attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    glm::vec3 worldFront;
};
