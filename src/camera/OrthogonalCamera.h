//
// Created by Luecx on 03.06.2021.
//

#ifndef ENGINE3D_SRC_CAMERA_ORTHOGONALCAMERA_H_
#define ENGINE3D_SRC_CAMERA_ORTHOGONALCAMERA_H_

#include "Camera.h"
class OrthogonalCamera : public Camera{

    private:
    float left = -3;
    float right = 3; float top = 3; float bottom = -3;
    float near = 0.01;
    float far = 5000;

    protected:
    void recomputeProjectionMatrix() override;

    public:
    float getLeft() const {
        return left;
    }
    void setLeft(float left) {
        OrthogonalCamera::left = left;
        projectionMatrixOutdated = true;
    }
    float getRight() const {
        return right;
    }
    void setRight(float right) {
        OrthogonalCamera::right = right;
        projectionMatrixOutdated = true;
    }
    float getTop() const {
        return top;
    }
    void setTop(float top) {
        OrthogonalCamera::top = top;
        projectionMatrixOutdated = true;
    }
    float getBottom() const {
        return bottom;
    }
    void setBottom(float bottom) {
        OrthogonalCamera::bottom = bottom;
        projectionMatrixOutdated = true;
    }
    float getNear() const {
        return near;
    }
    void setNear(float near) {
        OrthogonalCamera::near = near;
        projectionMatrixOutdated = true;
    }
    float getFar() const {
        return far;
    }
    void setFar(float far) {
        OrthogonalCamera::far = far;
        projectionMatrixOutdated = true;
    }
};

#endif    // ENGINE3D_SRC_CAMERA_ORTHOGONALCAMERA_H_
