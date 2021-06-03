//
// Created by Luecx on 02.06.2021.
//

#include "Camera.h"

#include <iostream>
Matrix<4, 4>& Camera::getViewMatrix() {
    if (viewMatrixOutdated) {
        viewMatrix = getAbsoluteTransformationMatrix().invert();
        viewMatrixOutdated = false;
    }
    return viewMatrix;
}
Matrix<4, 4>& Camera::getProjectionMatrix() {
    if (projectionMatrixOutdated) {
        recomputeProjectionMatrix();
        projectionMatrixOutdated = false;
    }
    return projectionMatrix;
}
void Camera::absoluteDataChangedNotification() {
    GroupableGameObject::absoluteDataChangedNotification();
    viewMatrixOutdated = true;
}
