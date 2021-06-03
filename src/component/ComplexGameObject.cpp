//
// Created by Luecx on 31.05.2021.
//

#include "ComplexGameObject.h"

#include <iostream>

ComplexGameObject::ComplexGameObject(const Vector<3>& position, const Vector<3>& rotation,
                                     const Vector<3>& scale)
    : position(position), rotation(rotation), scale(scale) {
}

Matrix<4, 4>& ComplexGameObject::getTransformationMatrix() {
    if (outdated) {
        outdated = false;
        updateTransformationMatrix();
    }
    return this->transformationMatrix;
}

void ComplexGameObject::setOutdated() {
    outdated = true;
    dataChangedNotification();
}

Vector<3>& ComplexGameObject::getPosition() {
    setOutdated();
    return position;
}
Vector<3>& ComplexGameObject::getRotation() {
    setOutdated();
    return rotation;
}
Vector<3>& ComplexGameObject::getScale() {
    setOutdated();
    return scale;
}
void ComplexGameObject::setPosition(const Vector<3>& position) {
    setOutdated();
    ComplexGameObject::position = position;
}
void ComplexGameObject::setRotation(const Vector<3>& rotation) {
    setOutdated();
    ComplexGameObject::rotation = rotation;
}
void ComplexGameObject::setScale(const Vector<3>& scale) {
    setOutdated();
    ComplexGameObject::scale = scale;
}

void ComplexGameObject::updateTransformationMatrix() {
    transformationMatrix.identity();
    transformationMatrix.translate3D(position);
    transformationMatrix.rotate3D(rotation[0] * M_PI / 180, {1, 0, 0});
    transformationMatrix.rotate3D(rotation[1] * M_PI / 180, {0, 1, 0});
    transformationMatrix.rotate3D(rotation[2] * M_PI / 180, {0, 0, 1});
    transformationMatrix.scale3D(scale);
}