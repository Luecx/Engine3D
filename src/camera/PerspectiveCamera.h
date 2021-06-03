//
// Created by Luecx on 02.06.2021.
//

#ifndef ENGINE3D_SRC_CAMERA_PERSPECTIVECAMERA_H_
#define ENGINE3D_SRC_CAMERA_PERSPECTIVECAMERA_H_

#include "Camera.h"

#include <GLFW/glfw3.h>
#include <iostream>

class PerspectiveCamera : public Camera {
    private:
    float fov         = 60;
    float nearPlane   = 0.01;
    float farPlane    = 5000;
    float aspectRatio = 1920.0 / 1080.0;

    void  recomputeProjectionMatrix() {
        projectionMatrix.clear();

//        int width,height;
//        glfwGetWindowSize(&width, &height);
//        std::cout << width << " " << height << std::endl;

//        float aspectRatio    = (float) Display.getDisplayMode().getWidth() / (float) Display.getDisplayMode().getHeight();
        Precision yScale         = (float) ((1.0 / tan((fov / 2.0) * M_PI / 180.0)));
        Precision xScale         = yScale / aspectRatio;
        Precision frustumLength  = farPlane - nearPlane;

//        projectionMatrix(0,0) = xScale;
//        projectionMatrix(1,1) = yScale;
//        projectionMatrix(2,2) = -((farPlane + nearPlane) / frustumLength);
//        projectionMatrix(3,2) = -1;
//        projectionMatrix(2,3) = -((2 * nearPlane * farPlane) / frustumLength);
        projectionMatrix(0,0) = xScale;
        projectionMatrix(1,1) = yScale;
        projectionMatrix(2,2) = -(farPlane+nearPlane) / frustumLength;
        projectionMatrix(3,2) = -1;
        projectionMatrix(2,3) = - 2 * nearPlane * farPlane / frustumLength;
//        projectionMatrix(3,3) = 1;
//        projectionMatrix(3,3) = 1;
    }

    float getFov() const {
        return fov;
    }
    void setFov(float fov) {
        fov = fov;
    }
};

#endif    // ENGINE3D_SRC_CAMERA_PERSPECTIVECAMERA_H_
