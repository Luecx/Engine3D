//
// Created by Luecx on 06.06.2021.
//

#ifndef ENGINE3D_SRC_LIGHT_LIGHTSOURCE_H_
#define ENGINE3D_SRC_LIGHT_LIGHTSOURCE_H_

#include "../math/Vector.h"

class LightSource {

    // color of light
    Vector<3> color;

    // strength of light, following a * b^{c*x} (realistic: b = 0.5, c = 1
    float     falloffStrength = 1;
    float     falloffBase     = 0.5;
    float     falloffExponent = 1;

    // 0 means no direction = point light
    Vector<3> direction {0, 0, 0};

    public:
    LightSource(const Vector<3> &color, float falloffStrength = 1, float falloff_base = 0.5, float falloff_exponent = 1);
};

#endif    // ENGINE3D_SRC_LIGHT_LIGHTSOURCE_H_
