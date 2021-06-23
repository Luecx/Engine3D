//
// Created by Luecx on 16.06.2021.
//

#ifndef ENGINE3D_SRC_COMPONENTS_NORMALMAP_H_
#define ENGINE3D_SRC_COMPONENTS_NORMALMAP_H_

#include "Texture.h"

struct NormalMap : public Texture{
    NormalMap();
    NormalMap(GLuint texture_id, int width, int height);
    NormalMap(Texture&& other);
    NormalMap(const Texture& other);
};

#endif    // ENGINE3D_SRC_COMPONENTS_COLORMAP_H_
