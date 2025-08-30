//
// Created by ChiroYuki on 30/08/2025.
//

#ifndef VOXELENGINE_TEXTURE_H
#define VOXELENGINE_TEXTURE_H

#include <string>
#include "glad/glad.h"

class Texture {
protected:
    GLuint ID;
    GLenum target;

public:
    explicit Texture(GLenum target);

    virtual ~Texture();

    void bind(int unit = 0) const;
};

#endif //VOXELENGINE_TEXTURE_H
