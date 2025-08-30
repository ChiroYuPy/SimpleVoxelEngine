//
// Created by ChiroYuki on 30/08/2025.
//

#ifndef VOXELENGINE_TEXTURE2D_H
#define VOXELENGINE_TEXTURE2D_H

#include "Texture.h"

class Texture2D : public Texture {
public:
    Texture2D(int width, int height, unsigned char *data);
};

#endif //VOXELENGINE_TEXTURE2D_H
