//
// Created by Luecx on 25.06.2021.
//

#ifndef ENGINE3D_SRC_COMPONENTS_SHADOWCASTER_H_
#define ENGINE3D_SRC_COMPONENTS_SHADOWCASTER_H_

#include "../buffer/FrameBufferObject.h"
#include "../config.h"
#include "../math/Precision.h"
struct ShadowCaster {

    Precision radius;
    Precision near;
    Precision far;

    FrameBufferObject frameBuffer{SHADOW_RESOLUTION, SHADOW_RESOLUTION};


    ShadowCaster(Precision radius = 5, Precision near = 0.01, Precision far = 10000);


};

#endif    // ENGINE3D_SRC_COMPONENTS_SHADOWCASTER_H_
