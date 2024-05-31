//
// Created by Luecx on 25.06.2021.
//

#ifndef ENGINE3D_SRC_COMPONENTS_SHADOWCASTER_H_
#define ENGINE3D_SRC_COMPONENTS_SHADOWCASTER_H_

#include "../buffer/FrameBufferObject.h"
#include "../core/config.h"
#include "../math/Precision.h"
#include "../math/Vector.h"
#include "../math/Matrix.h"

struct ShadowCaster {

    Precision         radius;
    Precision         near;
    Precision         far;

    // vector to target
    Vector<3>         target;
    Matrix<4, 4>      shadow_view;
    FrameBufferObject frameBuffer {SHADOW_RESOLUTION, SHADOW_RESOLUTION};

    ShadowCaster(Precision radius = 5, Precision near = 0.01, Precision far = 10000, const Vector<3>& target = {0, 0, 0});
};

#endif    // ENGINE3D_SRC_COMPONENTS_SHADOWCASTER_H_
