//
// Created by Luecx on 01.06.2021.
//

#include "Texture.h"

#include "../loader/TextureLoader.h"

#include <iostream>

bool Texture::load() {
    auto tex_data = loadTexture(path);
    textureId = std::get<0>(tex_data);
    width     = std::get<1>(tex_data);
    height    = std::get<2>(tex_data);
    loaded    = textureId != nullptr;

    return loaded;
}
void Texture::unload() {
    if (textureId != nullptr) {
        textureId = nullptr;
    }
    loaded = false;
}

Texture::Texture(const std::string& path)
    : Resource(path) {}
