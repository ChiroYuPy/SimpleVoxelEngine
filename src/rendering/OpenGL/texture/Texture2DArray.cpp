//
// Created by ChiroYuki on 30/08/2025.
//

#include "rendering/OpenGL/texture/Texture2DArray.h"

Texture2DArray::Texture2DArray(int width, int height, int layers, unsigned char *data)
        : TextureLayered(GL_TEXTURE_2D_ARRAY, layers) {
    bind();
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, width, height, layers,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
}
