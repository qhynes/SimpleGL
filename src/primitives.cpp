#include <SimpleGL/primitives.h>

MeshData Primitives::cube() {
    MeshData data;

    data.vertices = {
        // back face (-Z)
        {{-0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}},
        {{ 0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}},

        // front face (+Z)
        {{-0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}},

        // left face (-X)
        {{-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},

        // right face (+X)
        {{ 0.5f, -0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
        {{ 0.5f, -0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},

        // bottom face (-Y)
        {{-0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}},

        // top face (+Y)
        {{-0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}}
    };

    data.indices = {
        0, 1, 2,  2, 3, 0,       // back
        4, 5, 6,  6, 7, 4,       // front
        8, 9, 10, 10, 11, 8,     // left
        12, 13, 14, 14, 15, 12,  // right
        16, 17, 18, 18, 19, 16,  // bottom
        20, 21, 22, 22, 23, 20   // top
    };

    return data;
}

MeshData Primitives::grid(float width, float depth, int cols, int rows, bool singleUV) {
    MeshData data;

    float xStart = -width / 2;
    float zStart = width / 2;

    // how much space between x and z per col and row
    float xScale = width / cols;
    float zScale = -depth / rows;

    // how much between UV per col and row
    float uScale;
    float vScale;
    if (singleUV) {
        uScale = 1.0f / cols;
        vScale = 1.0f / rows;
    } else {
        uScale = 1.0f;
        vScale = 1.0f;
    }

    glm::vec3 normal(0.0f, 1.0f, 0.0f);

    for (int col = 0; col < cols + 1; col++) {
        for (int row = 0; row < rows + 1; row++) {
            float x = xStart + col * xScale;
            float z = zStart + row * zScale;
            float u = col * uScale;
            float v = row * vScale;
            
            glm::vec3 position(x, 0.0f, z);
            glm::vec2 uv(u, v);
            data.vertices.emplace_back(position, normal, uv);
        }
    }

    for (int col = 0; col < cols; col++) {
        for (int row = 0; row < rows; row++) {
            // v0 ---- v1
            // |    / |
            // |  /   |
            // |/     |
            // v2 ---- v3

            // 0, 2, 1
            // 1, 2, 3
            
            int topLeft = row * (cols + 1) + col;
            int topRight = topLeft + 1;
            int bottomLeft = (row + 1) * (cols + 1) + col;
            int bottomRight = bottomLeft + 1;

            data.indices.push_back(topLeft);
            data.indices.push_back(bottomLeft);
            data.indices.push_back(topRight);

            data.indices.push_back(topRight);
            data.indices.push_back(bottomLeft);
            data.indices.push_back(bottomRight);
        }
    }

    return data;
}

// creates a uv sphere mesh with the desired rows/colums of "quads"
MeshData Primitives::uv_sphere(int num_rows, int num_cols) {
    MeshData data;

    // create vertices
    for (int row = 0; row < num_rows + 1; row++) {
        float phi = M_PI - (M_PI * row / num_rows);
        for (int col = 0; col < num_cols + 1; col++) {
            float theta = 2.0 * M_PI - (2.0 * M_PI * col / num_cols);
            float unitX = std::sin(phi) * std::cos(theta);
            float unitY = std::cos(phi);
            float unitZ = std::sin(phi) * std::sin(theta);

            glm::vec3 position(unitX, unitY, unitZ);
            glm::vec3 normal(unitX, unitY, unitZ);
            glm::vec2 uv((float) col / num_cols, (float) row / num_rows);

            data.vertices.emplace_back(position, normal, uv);
        }
    }

    // create triangles
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            int topLeft = row * (num_cols + 1) + col;
            int topRight = topLeft + 1;
            int bottomLeft = (row + 1) * (num_cols + 1) + col;
            int bottomRight = bottomLeft + 1;

            data.indices.push_back(topLeft);
            data.indices.push_back(bottomLeft);
            data.indices.push_back(topRight);

            data.indices.push_back(topRight);
            data.indices.push_back(bottomLeft);
            data.indices.push_back(bottomRight);
        }
    }

    return data;
}

// MeshData cylinder(int segments) {
//     MeshData data;

//     data.vertices.resize(segments * 2 + 2);
//     data.textureCoords.resize((segments + 1) * 2);
//     for (int i = 0; i < segments; i++) {
//         float theta = i * 2 * M_PI / segments;
//         float x = std::cos(theta);
//         float z = std::sin(theta);
//         data.vertices[i] = Eigen::Vector3f(x, -1.0f, z);
//         data.textureCoords[i] = Eigen::Vector2f(1.0f - (float) i / segments, 0.0f);
//         data.vertices[i + segments] = Eigen::Vector3f(x, 1.0f, z);
//         data.textureCoords[i + segments + 1] = Eigen::Vector2f(1.0f - (float) i / segments, 1.0f);
//         data.normals.push_back(Eigen::Vector3f(x, 0.0f, z));

//         glm::vec3 position(x, -1.0f, z);
//         glm::vec3 normal(x, 0.0f, z);
//         glm::vec2 uv(1.0f - (float) i / segments, 0.0f);

//         data.vertices.emplace_back({position, normal, uv});
//     }
//     data.textureCoords[segments] = Eigen::Vector2f(0.0f, 0.0f);
//     data.textureCoords[2 * segments + 1] = Eigen::Vector2f(0.0f, 1.0f);

//     for (int i = 0; i < segments - 1; i++) {
//         data.triangles.push_back(tri(i, i + segments, i + 1, i, i, i + 1, i, i + segments + 1, i + 1, 0, color()));
//         data.triangles.push_back(tri(i + segments, i + segments + 1, i + 1, i, i + 1, i + 1, i + segments + 1, i + segments + 2, i + 1, 0, color()));
//     }

//     data.triangles.push_back(tri(segments - 1, 2 * segments - 1, 0, segments - 1, segments - 1, 0, segments - 1, 2 * segments, segments, 0, color()));
//     data.triangles.push_back(tri(2 * segments - 1, segments, 0, segments - 1, 0, 0, 2 * segments, 2 * segments + 1, segments, 0, color()));

//     // add top and bottom circles
//     m.vertices[2 * segments] = Eigen::Vector3f(0.0f, -1.0f, 0.0f);
//     m.normals.push_back(Eigen::Vector3f(0.0f, -1.0f, 0.0f));
//     for (int i = 0; i < segments; i++) {
//         m.triangles.push_back(tri(i, (i + 1) % segments, 2 * segments, segments, segments, segments, 0, 0, 0, 0, color()));
//     }

//     m.vertices[2 * segments + 1] = Eigen::Vector3f(0.0f, 1.0f, 0.0f);
//     m.normals.push_back(Eigen::Vector3f(0.0f, 1.0f, 0.0f));
//     m.normals.push_back(Eigen::Vector3f(0.0f, 1.0f, 0.0f));
//     for (int i = 0; i < segments; i++) {
//         m.triangles.push_back(tri((i + 1) % segments + segments, i + segments, 2 * segments + 1, segments + 1, segments + 1, segments + 1, 0, 0, 0, 0, color()));
//     }

//     return m;
// }
