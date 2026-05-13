#include <SimpleGL/camera.h>
#include <SimpleGL/window.h>

#include <iostream>

Camera::Camera(
    glm::vec3 position,
    glm::vec3 up,
    glm::vec3 front,
    float yaw,
    float pitch
) : position(position),
    worldUp(up),
    worldFront(front),
    yaw(yaw),
    pitch(pitch)
{
    recalculateVectors();
}

void Camera::update(const Input& input, float dt) {
    glm::vec3 movement(0.0f);

    if (input.isKeyDown(SDLK_w))
        movement += worldFront * speed * dt;
    if (input.isKeyDown(SDLK_s))
        movement -= worldFront * speed * dt;
    if (input.isKeyDown(SDLK_d))
        movement += right * speed * dt;
    if (input.isKeyDown(SDLK_a))
        movement -= right * speed * dt;
    if (input.isKeyDown(SDLK_SPACE))
        movement += worldUp * speed * dt;
    if (input.isKeyDown(SDLK_LSHIFT))
        movement -= worldUp * speed * dt;

    if (glm::length(movement) > 0.0f) {
        movement = glm::normalize(movement);
    }

    position += movement * speed * dt;
    
    yaw += input.mouseDeltaX * sensitivity;
    pitch -= input.mouseDeltaY * sensitivity;
    pitch = std::clamp(pitch, -89.0f, 89.0f);

    recalculateVectors();
    hasChanged = false;
}

void Camera::recalculateVectors() {
    // calculate the new front vector
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    // also re-calculate the right, up, and worldFront vectors
    right = glm::normalize(glm::cross(front, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, front));
    worldFront = glm::cross(worldUp, right);
}

// returns view matrix calculated using euler angles
glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

// used by renderer for specular lighting
glm::vec3 Camera::getPosition() const {
    return position;
}

float Camera::getFov() const {
    return fov;
}
