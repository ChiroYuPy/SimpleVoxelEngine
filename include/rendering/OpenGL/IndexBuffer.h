//
// Created by ChiroYuki on 30/08/2025.
//

#ifndef VOXELENGINE_INDEXBUFFER_H
#define VOXELENGINE_INDEXBUFFER_H

#include "Buffer.h"

#include <glad/glad.h>

class IndexBuffer : public Buffer {
private:
    size_t m_count;

public:
    IndexBuffer() : Buffer(GL_ELEMENT_ARRAY_BUFFER), m_count(0) {}

    IndexBuffer(const std::vector<unsigned int>& indices)
            : Buffer(GL_ELEMENT_ARRAY_BUFFER), m_count(indices.size()) {
        setData(indices);
    }

    size_t getCount() const { return m_count; }

    void setIndices(const std::vector<unsigned int>& indices) {
        m_count = indices.size();
        setData(indices);
    }
};

#endif //VOXELENGINE_INDEXBUFFER_H
