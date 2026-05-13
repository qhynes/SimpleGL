#pragma once

#include <vector>

#include <SimpleGL/mesh.h>

struct MeshData {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

namespace Primitives {
    MeshData quad();
    MeshData cube();
    MeshData grid(float width, float depth, int cols, int rows, bool singleUV);
    MeshData uv_sphere(int num_rows, int num_cols);
}