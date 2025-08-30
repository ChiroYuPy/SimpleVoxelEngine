//
// Created by ChiroYuki on 30/08/2025.
//

#include "rendering/OpenGL/RenderAPI.h"

#include "glad/glad.h"

void RenderAPI::SetClearColor(const float r, const float g, const float b, const float a) {
    glClearColor(r, g, b, a);
}

void RenderAPI::Clear(const bool color, const bool depth) {
    GLbitfield mask = 0;
    if (color) mask |= GL_COLOR_BUFFER_BIT;
    if (depth) mask |= GL_DEPTH_BUFFER_BIT;
    glClear(mask);
}

void RenderAPI::SetViewport(const unsigned int x, const unsigned int y, const unsigned int width,
                            const unsigned int height) {
    glViewport(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLint>(width), static_cast<GLint>(height));
}

void RenderAPI::EnableDepthTest(const bool enable) {
    if (enable) glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
}

void RenderAPI::SetDepthFunc(const DepthFunc func) {
    glDepthFunc(static_cast<GLenum>(func));
}

void RenderAPI::EnableFaceCulling(const bool enable) {
    if (enable) glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);
}

void RenderAPI::SetCullFace(const CullFace face) {
    glCullFace(static_cast<GLenum>(face));
}

void RenderAPI::SetPolygonMode(const PolygonFace face, const PolygonMode mode) {
    glPolygonMode(static_cast<GLenum>(face), static_cast<GLenum>(mode));
}

void RenderAPI::EnableBlending(const bool enable) {
    if (enable) glEnable(GL_BLEND);
    else
        glDisable(GL_BLEND);
}

void RenderAPI::SetBlendFunc(const BlendFactor src, const BlendFactor dst) {
    glBlendFunc(static_cast<GLenum>(src), static_cast<GLenum>(dst));
}

void RenderAPI::DrawArrays(const DrawMode mode, const uint32_t first, const uint32_t count) {
    glDrawArrays(static_cast<GLenum>(mode), static_cast<GLint>(first), static_cast<GLsizei>(count));
}

void RenderAPI::DrawElements(const DrawMode mode, const uint32_t count, const uint32_t type, const void *indices) {
    glDrawElements(static_cast<GLenum>(mode), static_cast<GLsizei>(count), static_cast<GLenum>(type), indices);
}

void RenderAPI::DrawArraysInstanced(const DrawMode mode, const uint32_t first, const uint32_t count,
                                    const uint32_t instanceCount) {
    glDrawArraysInstanced(static_cast<GLenum>(mode), static_cast<GLint>(first), static_cast<GLsizei>(count),
                          static_cast<GLsizei>(instanceCount));
}

void
RenderAPI::DrawElementsInstanced(const DrawMode mode, const uint32_t count, const uint32_t type, const void *indices,
                                 const uint32_t instanceCount) {
    glDrawElementsInstanced(static_cast<GLenum>(mode), static_cast<GLsizei>(count), static_cast<GLenum>(type), indices,
                            static_cast<GLsizei>(instanceCount));
}

const char *RenderAPI::GetRenderer() {
    return reinterpret_cast<const char *>(glGetString(GL_RENDERER));
}

const char *RenderAPI::GetVersion() {
    return reinterpret_cast<const char *>(glGetString(GL_VERSION));
}

int RenderAPI::GetMaxTextureUnits() {
    int maxUnits;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxUnits);
    return maxUnits;
}