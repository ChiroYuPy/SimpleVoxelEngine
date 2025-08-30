//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_RENDERER_H
#define PIXLENGINE_RENDERER_H

#include <GLT.h>
#include <iostream>
#include <memory>
#include "rendering/OpenGL/Shader.h"
#include "Camera.h"
#include "voxelEngine/voxelWorld/chunk/ChunkMesh.h"

class Renderer {
public:
    Renderer() = default;

    ~Renderer() = default;

    bool initialize();

    void setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

    void setClearColor(const glm::vec4 &color);

    void clear();
};

#endif //PIXLENGINE_RENDERER_H