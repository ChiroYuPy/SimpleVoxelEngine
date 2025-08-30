//
// Created by ChiroYuki on 30/08/2025.
//

#include "rendering/OpenGL/texture/Texture.h"

Texture::Texture(GLenum target) : target(target), ID(0) {
    glGenTextures(1, &ID);
}

Texture::~Texture() {
    glDeleteTextures(1, &ID);
}

void Texture::bind(int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(target, ID);
}
