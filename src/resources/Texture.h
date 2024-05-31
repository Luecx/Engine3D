//
// Created by Luecx on 01.06.2021.
//

#ifndef ENGINE3D_SRC_MODEL_TEXTURE_H_
#define ENGINE3D_SRC_MODEL_TEXTURE_H_

#include "../gldata/TextureID.h"
#include "Resource.h"

#include <string>

class Texture : public Resource{
    public:
    TextureIDPtr textureId = nullptr;
    int          width;
    int          height;

    public:
    explicit Texture(const std::string& path = "");

    public:
    bool load() override;
    void unload() override;
};

using TexturePtr = std::shared_ptr<Texture>;

#endif    // ENGINE3D_SRC_MODEL_TEXTURE_H_
