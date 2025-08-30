//
// Created by ChiroYuki on 30/08/2025.
//

#ifndef VOXELENGINE_VERTEXARRAY_H
#define VOXELENGINE_VERTEXARRAY_H

#include "Buffer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <glad/glad.h>
#include <memory>

class VertexArray {
private:
    GLuint ID;
    std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
    std::shared_ptr<IndexBuffer> m_indexBuffer;

public:
    VertexArray() {
        glGenVertexArrays(1, &ID);
    }

    ~VertexArray() {
        glDeleteVertexArrays(1, &ID);
    }

    void bind() const {
        glBindVertexArray(ID);
    }

    void unbind() const {
        glBindVertexArray(0);
    }

    void addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer,
                         GLuint index, GLint size, GLenum type,
                         GLboolean normalized = GL_FALSE,
                         GLsizei stride = 0, const void* pointer = nullptr) {
        bind();
        buffer->bind();

        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);

        m_vertexBuffers.push_back(buffer);
    }

    void setIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) {
        bind();
        buffer->bind();
        m_indexBuffer = buffer;
    }

    std::shared_ptr<IndexBuffer> getIndexBuffer() const { return m_indexBuffer; }
};

#endif //VOXELENGINE_VERTEXARRAY_H
