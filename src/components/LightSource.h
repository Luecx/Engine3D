//
// Created by Luecx on 06.06.2021.
//

#ifndef ENGINE3D_SRC_LIGHT_LIGHTSOURCE_H_
#define ENGINE3D_SRC_LIGHT_LIGHTSOURCE_H_

#include "../math/Vector.h"

struct LightSource {

    // color of light
    Vector<3> color;

    // strength of light, following a * b^{c*x} (realistic: b = 0.5, c = 1
    Vector<3> falloff;

    public:
    LightSource(const Vector<3> &p_color = {1,1,1},
                const Vector<3> &p_falloff = {1,0.5,1}) : color(p_color), falloff(p_falloff) {
    }
};

#endif    // ENGINE3D_SRC_LIGHT_LIGHTSOURCE_H_
