#pragma once

#include <SimpleGL/buffers.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;

    Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 uv) : position(position), normal(normal), uv(uv) {}
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

    void draw() const;
    void update(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

// private:
    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ibo;
};
