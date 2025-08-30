//
// Created by ChiroYuki on 30/08/2025.
//

#ifndef VOXELENGINE_TEXTURELAYERED_H
#define VOXELENGINE_TEXTURELAYERED_H

#include "Texture.h"

class TextureLayered : public Texture {
protected:
    int layers;

public:
    TextureLayered(GLenum target, int layers);

    int getLayerCount() const { return layers; }
};

#endif //VOXELENGINE_TEXTURELAYERED_H
