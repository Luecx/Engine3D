//
// Created by Luecx on 31.05.2021.
//

#include "ComplexTransformation.h"

#include <iostream>
ComplexTransformation::ComplexTransformation(const Vector<3>& position, const Vector<3>& rotation, const Vector<3>& scale)
    : Transformation(position, rotation, scale) {
}
Matrix<4, 4>& ComplexTransformation::getAbsoluteTransformationMatrix() {
    if (this->absoluteOutdated) {
        updateAbsoluteTransformationMatrix();
    }
    return absoluteTransformationMatrix;
}
Vector<3>& ComplexTransformation::getAbsolutePosition() {
    if (this->absoluteOutdated) {
        updateAbsoluteTransformationMatrix();
    }
    return absolutePosition;
}

Vector<3> ComplexTransformation::getXAxis() {
    if (this->absoluteOutdated) {
        updateAbsoluteTransformationMatrix();
    }
    return {absoluteTransformationMatrix(0, 0), absoluteTransformationMatrix(1, 0), absoluteTransformationMatrix(2, 0)};
}
Vector<3> ComplexTransformation::getYAxis() {
    if (this->absoluteOutdated) {
        updateAbsoluteTransformationMatrix();
    }
    return {absoluteTransformationMatrix(0, 1), absoluteTransformationMatrix(1, 1), absoluteTransformationMatrix(2, 1)};
}
Vector<3> ComplexTransformation::getZAxis() {
    if (this->absoluteOutdated) {
        updateAbsoluteTransformationMatrix();
    }
    return {absoluteTransformationMatrix(0, 2), absoluteTransformationMatrix(1, 2), absoluteTransformationMatrix(2, 2)};
}

void ComplexTransformation::setAbsoluteOutdated() {
    for (ComplexTransformation* g : childs) {
        g->setAbsoluteOutdated();
    }
    this->absoluteOutdated = true;
    absoluteDataChangedNotification();
}
bool ComplexTransformation::hasParent() {
    return (this->parent != nullptr);
}
bool ComplexTransformation::setParent(ComplexTransformation* parent) {
    if (this->parent == parent || std::find(childs.begin(), childs.end(), parent) != childs.end()) {
        return false;
    }
    this->parent = parent;
    this->parent->childs.push_back(this);
    setAbsoluteOutdated();
    return true;
}
bool ComplexTransformation::removeParent() {
    if (this->parent == nullptr) {
        return false;
    }
    this->parent->childs.erase(std::remove(this->parent->childs.begin(), this->parent->childs.end(), this), this->parent->childs.end());
    this->parent = nullptr;
    setAbsoluteOutdated();
    return true;
}
bool ComplexTransformation::addChild(ComplexTransformation* child) {
    return child->setParent(this);
}
bool ComplexTransformation::removeChild(ComplexTransformation* child) {
    return child->removeParent();
}
std::vector<ComplexTransformation*> ComplexTransformation::getChilds() {
    return this->childs;
}
void ComplexTransformation::dataChangedNotification() {
    this->setAbsoluteOutdated();
}
void ComplexTransformation::updateAbsoluteTransformationMatrix() {
    if (!this->absoluteOutdated)
        return;
    if (this->parent == nullptr) {
        this->absoluteTransformationMatrix = this->getTransformationMatrix();
        this->absolutePosition             = this->position;
        this->absoluteOutdated             = false;
    } else {
        if (this->parent->absoluteOutdated) {
            this->parent->updateAbsoluteTransformationMatrix();
        }

        this->absoluteTransformationMatrix = this->parent->absoluteTransformationMatrix * this->getTransformationMatrix();

        this->absolutePosition[0]          = this->absoluteTransformationMatrix(3, 0);
        this->absolutePosition[0]          = this->absoluteTransformationMatrix(3, 1);
        this->absolutePosition[0]          = this->absoluteTransformationMatrix(3, 2);
        this->absoluteOutdated             = false;
    }
}
ComplexTransformation::~ComplexTransformation() {
    for (int i = childs.size() - 1; i >= 0; i--) {
        childs[i]->removeParent();
    }
}
