//
// Created by ChiroYuki on 30/08/2025.
//

#ifndef VOXELENGINE_TEXTURE2DARRAY_H
#define VOXELENGINE_TEXTURE2DARRAY_H

#include "TextureLayered.h"

class Texture2DArray : public TextureLayered {
public:
    Texture2DArray(int width, int height, int layers, unsigned char *data);
};

#endif //VOXELENGINE_TEXTURE2DARRAY_H
