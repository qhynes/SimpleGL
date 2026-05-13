#pragma once

#include "glad/glad.h"
#include <cstddef>

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    static void unbind();
    void addFloatAttribute(GLuint index, GLint componentCount, GLsizei stride, std::size_t offset);

private:
    GLuint m_id = 0;
};

class VertexBuffer {
public:
    VertexBuffer(const void* data, std::size_t sizeBytes);
    ~VertexBuffer();

    void bind() const;
    static void unbind();
    void setData(const void* data, std::size_t sizeBytes);

// private:
    GLuint m_id = 0;
};

class IndexBuffer {
public:
    IndexBuffer(const unsigned int* data, std::size_t count);
    ~IndexBuffer();

    void bind() const;
    static void unbind();
    void setData(const uint32_t* data, std::size_t count);
    std::size_t count() const;

private:
    GLuint m_id = 0;
    std::size_t m_count = 0;
};
