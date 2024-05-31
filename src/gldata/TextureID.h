//
// Created by finn on 5/22/24.
//

#ifndef ENGINE3D_TEXTUREID_H
#define ENGINE3D_TEXTUREID_H

#include "GLData.h"

#include <memory>


class TextureID : public GLData{
    public:
    TextureID();
    ~TextureID();

    public:
    void bind() override;
    void unbind() override;
};

using TextureIDPtr = std::shared_ptr<TextureID>;

#endif    // ENGINE3D_TEXTUREID_H
