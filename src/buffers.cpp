#include <SimpleGL/buffers.h>

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind() const {
    glBindVertexArray(m_id);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

void VertexArray::addFloatAttribute(GLuint index, GLint componentCount, GLsizei stride, std::size_t offset) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, componentCount, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void*>(offset));
}


VertexBuffer::VertexBuffer(const void* data, std::size_t sizeBytes) {
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, sizeBytes, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_id);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setData(const void* data, std::size_t sizeBytes) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, sizeBytes, data, GL_STATIC_DRAW);
}


IndexBuffer::IndexBuffer(const unsigned int* data, std::size_t count) : m_count(count) {
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_id);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::setData(const uint32_t* data, std::size_t count) {
    m_count = count;
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
}

std::size_t IndexBuffer::count() const {
    return m_count;
}
