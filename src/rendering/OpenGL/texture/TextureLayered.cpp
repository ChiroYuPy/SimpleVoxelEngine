//
// Created by ChiroYuki on 30/08/2025.
//

#include "rendering/OpenGL/texture/TextureLayered.h"

TextureLayered::TextureLayered(GLenum target, int layers) : Texture(target), layers(layers) {}
