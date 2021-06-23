//
// Created by Luecx on 16.06.2021.
//

#ifndef ENGINE3D_SRC_COMPONENTS_PARALLAXMAP_H_
#define ENGINE3D_SRC_COMPONENTS_PARALLAXMAP_H_

#include "Texture.h"

struct ParallaxMap : public Texture{

    public:
    float depth;

    ParallaxMap();
    ParallaxMap(float depth);
    ParallaxMap(GLuint texture_id, int width, int height, float depth);
    ParallaxMap(Texture&& other, float depth);
    ParallaxMap(const Texture& other, float depth);
};

#endif    // ENGINE3D_SRC_COMPONENTS_COLORMAP_H_
