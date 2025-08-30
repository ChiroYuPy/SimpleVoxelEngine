//
// Created by ChiroYuki on 30/08/2025.
//

#ifndef VOXELENGINE_BUFFER_H
#define VOXELENGINE_BUFFER_H

#include <glad/glad.h>

#include <vector>

class Buffer {
protected:
    GLuint ID;
    GLenum m_target;
    GLenum m_usage;

public:
    Buffer(GLenum target = GL_ARRAY_BUFFER, GLenum usage = GL_STATIC_DRAW)
            : m_target(target), m_usage(usage) {
        glGenBuffers(1, &ID);
    }

    virtual ~Buffer() {
        glDeleteBuffers(1, &ID);
    }

    void bind() const {
        glBindBuffer(m_target, ID);
    }

    void unbind() const {
        glBindBuffer(m_target, 0);
    }

    void setData(const void* data, size_t size) const {
        bind();
        glBufferData(m_target, static_cast<GLsizeiptr>(size), data, m_usage);
    }

    template<typename T>
    void setData(const std::vector<T>& data) {
        setData(data.data(), data.size() * sizeof(T));
    }

    GLuint getId() const { return ID; }
};

#endif //VOXELENGINE_BUFFER_H
