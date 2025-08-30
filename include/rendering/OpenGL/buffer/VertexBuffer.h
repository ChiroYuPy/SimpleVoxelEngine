//
// Created by ChiroYuki on 30/08/2025.
//

#ifndef VOXELENGINE_VERTEXBUFFER_H
#define VOXELENGINE_VERTEXBUFFER_H

#include "Buffer.h"

#include "glad/glad.h"

class VertexBuffer : public Buffer {
public:
    VertexBuffer() : Buffer(GL_ARRAY_BUFFER) {}

    template<typename T>
    VertexBuffer(const std::vector<T> &vertices) : Buffer(GL_ARRAY_BUFFER) {
        setData(vertices);
    }
};

#endif //VOXELENGINE_VERTEXBUFFER_H
