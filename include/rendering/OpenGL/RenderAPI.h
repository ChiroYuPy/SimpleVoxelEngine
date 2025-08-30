//
// Created by ChiroYuki on 30/08/2025.
//

#ifndef VOXELENGINE_RENDERAPI_H
#define VOXELENGINE_RENDERAPI_H

#include <glm/glm.hpp>

#include <glad/glad.h>

#include <cstdint>

enum class DepthFunc : uint32_t {
    Never = GL_NEVER,
    Less = GL_LESS,
    LessOrEqual = GL_LEQUAL,
    Equal = GL_EQUAL,
    NotEqual = GL_NOTEQUAL,
    GreaterOrEqual = GL_GEQUAL,
    Greater = GL_GREATER,
    Always = GL_ALWAYS
};

enum class CullFace : uint32_t {
    Front = GL_FRONT,
    Back = GL_BACK,
    Both = GL_FRONT_AND_BACK
};

enum class PolygonFace : uint32_t {
    Front = GL_FRONT,
    Back = GL_BACK,
    Both = GL_FRONT_AND_BACK
};

enum class PolygonMode : uint32_t {
    Fill = GL_FILL,
    Line = GL_LINE,
    Point = GL_POINT
};

enum class BlendFactor : uint32_t {
    Zero = GL_ZERO,
    One = GL_ONE,
    SrcAlpha = GL_SRC_ALPHA,
    OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
};

enum class DrawMode : uint32_t {
    Points = GL_POINTS,
    Lines = GL_LINES,
    LineStrip = GL_LINE_STRIP,
    LineLoop = GL_LINE_LOOP,
    Triangles = GL_TRIANGLES,
    TriangleStrip = GL_TRIANGLE_STRIP,
    TriangleFan = GL_TRIANGLE_FAN
};

class RenderAPI {
public:
    // Framebuffer / Viewport State
    static void SetClearColor(float r, float g, float b, float a = 1.0f);

    static void Clear(bool color = true, bool depth = true);

    static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

    // Depth / Face Culling State
    static void EnableDepthTest(bool enable = true);

    static void SetDepthFunc(DepthFunc func);

    static void EnableFaceCulling(bool enable = true);

    static void SetCullFace(CullFace face);

    static void SetPolygonMode(PolygonFace face, PolygonMode mode);

    // Blending State
    static void EnableBlending(bool enable = true);

    static void SetBlendFunc(BlendFactor src, BlendFactor dst);

    // Draw Commands
    static void DrawArrays(DrawMode mode, uint32_t first, uint32_t count);

    static void DrawElements(DrawMode mode, uint32_t count, uint32_t type, const void *indices);

    static void DrawArraysInstanced(DrawMode mode, uint32_t first, uint32_t count, uint32_t instanceCount);

    static void
    DrawElementsInstanced(DrawMode mode, uint32_t count, uint32_t type, const void *indices, uint32_t instanceCount);

    // System / GPU Info
    static const char *GetRenderer();

    static const char *GetVersion();

    static int GetMaxTextureUnits();
};

#endif //VOXELENGINE_RENDERAPI_H
