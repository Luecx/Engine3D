//
// Created by Luecx on 16.06.2021.
//

#ifndef ENGINE3D_SRC_COMPONENTS_COLORMAP_H_
#define ENGINE3D_SRC_COMPONENTS_COLORMAP_H_

#include "Texture.h"

struct ColorMap : public Texture{
    ColorMap();
    ColorMap(GLuint texture_id, int width, int height);
    explicit ColorMap(Texture&& other);
    explicit ColorMap(const Texture& other);
};


#endif    // ENGINE3D_SRC_COMPONENTS_COLORMAP_H_
