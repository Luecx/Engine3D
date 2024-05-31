//
// Created by Luecx on 02.06.2021.
//

#ifndef ENGINE3D_SRC_CAMERA_CAMERA_H_
#define ENGINE3D_SRC_CAMERA_CAMERA_H_

#include "../transformation/ComplexTransformation.h"

class Camera : public ComplexTransformation {

    public:
    virtual Matrix<4, 4>& getViewMatrix();
    virtual Matrix<4, 4>& getProjectionMatrix();

    protected:
    bool         viewMatrixOutdated       = true;
    bool         projectionMatrixOutdated = true;

    Matrix<4, 4> viewMatrix {};
    Matrix<4, 4> projectionMatrix {};

    virtual void recomputeProjectionMatrix() = 0;
    void         absoluteDataChangedNotification() override;
};

#endif    // ENGINE3D_SRC_CAMERA_CAMERA_H_
