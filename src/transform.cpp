#include <SimpleGL/transform.h>

glm::mat4 Transform::getMatrix() const {
    glm::mat4 transform = glm::mat4(1.0f);

    // translation
    transform = glm::translate(transform, position);

    // rotation
    transform = glm::rotate(
        transform,
        glm::radians(rotation.x),
        glm::vec3(1.0f, 0.0f, 0.0f)
    );

    transform = glm::rotate(
        transform,
        glm::radians(rotation.y),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    transform = glm::rotate(
        transform,
        glm::radians(rotation.z),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );

    // scale
    transform = glm::scale(transform, uniformScale * scale);

    return transform;
}