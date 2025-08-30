//
// Created by ChiroYuki on 30/08/2025.
//

#ifndef VOXELENGINE_TEXTURECUBEMAP_H
#define VOXELENGINE_TEXTURECUBEMAP_H

#include "TextureLayered.h"

class TextureCubeMap : public TextureLayered {
public:
    TextureCubeMap(int size, unsigned char *faces[6]);
};

#endif //VOXELENGINE_TEXTURECUBEMAP_H
