//
// Created by Luecx on 03.06.2021.
//

#ifndef ENGINE3D_SRC_CAMERA_ORTHOGONALCAMERA_H_
#define ENGINE3D_SRC_CAMERA_ORTHOGONALCAMERA_H_

#include "Camera.h"
class OrthogonalCamera : public Camera {

    public:
    float left   = -3;
    float right  = 3;
    float top    = 3;
    float bottom = -3;
    float near   = 0.01;
    float far    = 5000;

    protected:
    void recomputeProjectionMatrix() override;
};

#endif    // ENGINE3D_SRC_CAMERA_ORTHOGONALCAMERA_H_
