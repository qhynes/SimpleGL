#include <SimpleGL/mesh.h>

#include "glad/glad.h"

Mesh::Mesh(const std::vector<Vertex>& vertices,
           const std::vector<uint32_t>& indices
) : vao(),
    vbo(vertices.data(), vertices.size() * sizeof(Vertex)),
    ibo(indices.data(), indices.size()) {
    
    vao.bind();
    vbo.bind();
    ibo.bind();
    
    vao.addFloatAttribute(0, 3, sizeof(Vertex), offsetof(Vertex, position));
    vao.addFloatAttribute(1, 3, sizeof(Vertex), offsetof(Vertex, normal));
    vao.addFloatAttribute(2, 2, sizeof(Vertex), offsetof(Vertex, uv));
}

void Mesh::draw() const {
    vao.bind();
    ibo.bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(ibo.count()), GL_UNSIGNED_INT, nullptr);
}

void Mesh::update(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
    vbo.setData(vertices.data(), vertices.size() * sizeof(Vertex));
    ibo.setData(indices.data(), indices.size());
}
