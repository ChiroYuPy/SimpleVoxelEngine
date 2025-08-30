//
// Created by ChiroYuki on 30/08/2025.
//

#include "rendering/OpenGL/texture/Texture2D.h"

Texture2D::Texture2D(int width, int height, unsigned char *data)
        : Texture(GL_TEXTURE_2D) {
    bind();
    glTexImage2D(target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(target);
}
