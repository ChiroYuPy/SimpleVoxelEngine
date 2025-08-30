//
// Created by ChiroYuki on 30/08/2025.
//

#include "rendering/OpenGL/texture/TextureCubeMap.h"

TextureCubeMap::TextureCubeMap(int size, unsigned char **faces)
        : TextureLayered(GL_TEXTURE_CUBE_MAP, 6) {
    bind();
    for (int i = 0; i < 6; i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
                     size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, faces[i]);
    }
}
