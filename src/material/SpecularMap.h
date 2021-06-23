//
// Created by Luecx on 16.06.2021.
//

#ifndef ENGINE3D_SRC_COMPONENTS_SpecularMap_H_
#define ENGINE3D_SRC_COMPONENTS_SpecularMap_H_

#include "Texture.h"

struct SpecularMap : public Texture{
    SpecularMap();
    SpecularMap(GLuint texture_id, int width, int height);
    SpecularMap(Texture&& other);
    SpecularMap(const Texture& other);
};

#endif    // ENGINE3D_SRC_COMPONENTS_COLORMAP_H_
