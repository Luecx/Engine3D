//
// Created by Luecx on 31.05.2021.
//

#include "GroupableGameObject.h"

#include <iostream>
GroupableGameObject::GroupableGameObject(const Vector<3>& position, const Vector<3>& rotation,
                                         const Vector<3>& scale)
    : ComplexGameObject(position, rotation, scale) {
}
Matrix<4, 4>& GroupableGameObject::getAbsoluteTransformationMatrix() {
    if (this->absoluteOutdated) {
        updateAbsoluteTransformationMatrix();
    }
    return absoluteTransformationMatrix;
}
Vector<3>& GroupableGameObject::getAbsolutePosition() {
    if (this->absoluteOutdated) {
        updateAbsoluteTransformationMatrix();
    }
    return absolutePosition;
}
void GroupableGameObject::setAbsoluteOutdated() {
    for(GroupableGameObject* g:childs){
        g->setAbsoluteOutdated();
    }
    this->absoluteOutdated = true;
    absoluteDataChangedNotification();
}
bool GroupableGameObject::hasParent() {
    return (this->parent != nullptr);
}
bool GroupableGameObject::setParent(GroupableGameObject* parent) {
    if (this->parent == parent || std::find(childs.begin(), childs.end(), parent) != childs.end()) {
        return false;
    }
    this->parent = parent;
    this->parent->childs.push_back(this);
    setAbsoluteOutdated();
    return true;
}
bool GroupableGameObject::removeParent() {
    if (this->parent == nullptr) {
        return false;
    }
    this->parent->childs.erase(
        std::remove(this->parent->childs.begin(), this->parent->childs.end(), this),
        this->parent->childs.end());
    this->parent           = nullptr;
    setAbsoluteOutdated();
    return true;
}
bool GroupableGameObject::addChild(GroupableGameObject* child) {
    return child->setParent(this);
}
bool GroupableGameObject::removeChild(GroupableGameObject* child) {
    return child->removeParent();
}
std::vector<GroupableGameObject*> GroupableGameObject::getChilds() {
    return this->childs;
}
void GroupableGameObject::dataChangedNotification() {
    this->setAbsoluteOutdated();
}
void GroupableGameObject::updateAbsoluteTransformationMatrix() {
    if(!this->absoluteOutdated) return;
    if (this->parent == nullptr) {
        this->absoluteTransformationMatrix = this->getTransformationMatrix();
        this->absolutePosition             = this->position;
        this->absoluteOutdated             = false;
    } else {
        if (this->parent->absoluteOutdated) {
            this->parent->updateAbsoluteTransformationMatrix();
        }

        this->absoluteTransformationMatrix =
            this->parent->absoluteTransformationMatrix * this->getTransformationMatrix();

        this->absolutePosition[0] = this->absoluteTransformationMatrix(3, 0);
        this->absolutePosition[0] = this->absoluteTransformationMatrix(3, 1);
        this->absolutePosition[0] = this->absoluteTransformationMatrix(3, 2);
        this->absoluteOutdated    = false;
    }
}
