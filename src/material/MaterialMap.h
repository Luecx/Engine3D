//
// Created by Luecx on 16.06.2021.
//

#ifndef ENGINE3D_SRC_COMPONENTS_COLORMAP_H_
#define ENGINE3D_SRC_COMPONENTS_COLORMAP_H_

#include "../resources/Texture.h"

struct MaterialMap {
    TexturePtr map;

    MaterialMap(const TexturePtr& map = nullptr);
};

struct ColorMap : MaterialMap {
    ColorMap(const TexturePtr& map = nullptr);
};

struct NormalMap : MaterialMap {
    NormalMap(const TexturePtr& map = nullptr);
};

struct SpecularMap : MaterialMap {
    SpecularMap(const TexturePtr& map = nullptr);
};

struct ParallaxMap : MaterialMap {
    float height_scale;

    ParallaxMap(const TexturePtr& map = nullptr, float heightScale = 1.0);
};

#endif    // ENGINE3D_SRC_COMPONENTS_COLORMAP_H_
