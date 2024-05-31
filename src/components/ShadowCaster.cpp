//
// Created by Luecx on 25.06.2021.
//

#include "ShadowCaster.h"
ShadowCaster::ShadowCaster(Precision radius, Precision near, Precision far)
    : radius(radius)
    , near(near)
    , far(far) {
    this->frameBuffer.createDepthBufferAttachment(SHADOW_RESOLUTION, SHADOW_RESOLUTION);
}
