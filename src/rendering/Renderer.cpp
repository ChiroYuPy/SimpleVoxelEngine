//
// Created by ChiroYuki on 19/07/2025.
//

#include "rendering/Renderer.h"
#include "rendering/Shader.h"
#include "core/Logger.h"

#include "rendering/OpenGL/RenderAPI.h"

bool Renderer::initialize() {
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glEnable(GL_MULTISAMPLE);

    return true;
}

void Renderer::setClearColor(const glm::vec4& color) {
    RenderAPI::SetClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::clear() {
    RenderAPI::Clear();
}

void Renderer::setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    RenderAPI::SetViewport(x, y, width, height);
}