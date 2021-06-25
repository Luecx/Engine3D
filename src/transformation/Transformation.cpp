//
// Created by Luecx on 31.05.2021.
//

#include "Transformation.h"

#include "../math/angle.h"

#include <iostream>

Transformation::Transformation(const Vector<3>& position, const Vector<3>& rotation,
                                     const Vector<3>& scale)
    : position(position), rotation(rotation), scale(scale) {
}

Matrix<4, 4>& Transformation::getTransformationMatrix() {
    if (outdated) {
        outdated = false;
        updateTransformationMatrix();
    }
    return this->transformationMatrix;
}

void Transformation::setOutdated() {
    outdated = true;
    dataChangedNotification();
}

Vector<3>& Transformation::getPosition() {
    setOutdated();
    return position;
}
Vector<3>& Transformation::getRotation() {
    setOutdated();
    return rotation;
}
Vector<3>& Transformation::getScale() {
    setOutdated();
    return scale;
}
void Transformation::setPosition(const Vector<3>& position) {
    setOutdated();
    Transformation::position = position;
}
void Transformation::setRotation(const Vector<3>& rotation) {
    setOutdated();
    Transformation::rotation = rotation;
}
void Transformation::setScale(const Vector<3>& scale) {
    setOutdated();
    Transformation::scale = scale;
}
void Transformation::rotate(const Vector<3>& axis, Precision angle){
    setOutdated();
    Vector<3> axisNorm = axis;
    axisNorm.normalise();

    Matrix<4,4> rotationMatrix{};
    rotationMatrix.identity();
    rotationMatrix.rotate3D(toRadians(angle), axisNorm);

    Matrix<4,4> newTransformationMatrix = rotationMatrix * transformationMatrix;
    Vector<3> newRotation = matrixToDegrees(newTransformationMatrix);
    this->setRotation(newRotation);

    getTransformationMatrix();
}

void Transformation::updateTransformationMatrix() {
    transformationMatrix.identity();
    transformationMatrix.translate3D(position);
    transformationMatrix.rotate3D(rotation[2] * M_PI / 180, {0, 0, 1});
    transformationMatrix.rotate3D(rotation[1] * M_PI / 180, {0, 1, 0});
    transformationMatrix.rotate3D(rotation[0] * M_PI / 180, {1, 0, 0});
    transformationMatrix.scale3D(scale);
}