//
// Created by Luecx on 03.06.2021.
//

#include "OrthogonalCamera.h"
void OrthogonalCamera::recomputeProjectionMatrix() {

    projectionMatrix.clear();

    projectionMatrix(0, 0) = 2 / (right - left);
    projectionMatrix(1, 1) = 2 / (top - bottom);
    projectionMatrix(2, 2) = -2 / (far - near);
    projectionMatrix(3, 3) = 1;
    projectionMatrix(0, 3) = -(right + left) / (right - left);
    projectionMatrix(1, 3) = -(top + bottom) / (top - bottom);
    projectionMatrix(2, 3) = -(far + near) / (far - near);
}
