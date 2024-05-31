//
// Created by Luecx on 02.06.2021.
//

#ifndef ENGINE3D_SRC_CAMERA_PERSPECTIVECAMERA_H_
#define ENGINE3D_SRC_CAMERA_PERSPECTIVECAMERA_H_

#include "../math/Projection.h"
#include "Camera.h"

#include <GLFW/glfw3.h>
#include <iostream>

class PerspectiveCamera : public Camera {
    public:
    float fov         = 60;
    float nearPlane   = 0.01;
    float farPlane    = 5000;
    float aspectRatio = 1920.0 / 1080.0;

    void  recomputeProjectionMatrix() {
        projectionMatrix = perspective(fov, aspectRatio, nearPlane, farPlane);
    }
};

#endif    // ENGINE3D_SRC_CAMERA_PERSPECTIVECAMERA_H_
