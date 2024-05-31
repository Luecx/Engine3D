//
// Created by Luecx on 16.06.2021.
//
#include "MaterialMap.h"

MaterialMap::MaterialMap(const TexturePtr& map)
    : map(map) {}

ParallaxMap::ParallaxMap(const TexturePtr& map, float heightScale)
    : MaterialMap(map)
    , height_scale(heightScale) {}

ColorMap::ColorMap(const TexturePtr& map)
    : MaterialMap(map) {}

NormalMap::NormalMap(const TexturePtr& map)
    : MaterialMap(map) {}

SpecularMap::SpecularMap(const TexturePtr& map)
    : MaterialMap(map) {}
