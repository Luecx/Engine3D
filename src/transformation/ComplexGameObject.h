//
// Created by Luecx on 31.05.2021.
//

#ifndef ENGINE3D_COMPONENT_COMPLEXGAMEOBJECT_H_
#define ENGINE3D_COMPONENT_COMPLEXGAMEOBJECT_H_

#include "../math/Matrix.h"
#include "../math/Vector.h"
#include "math.h"

struct ComplexGameObject {

    protected:
    Vector<3>    position {};
    Vector<3>    rotation {};
    Vector<3>    scale {1, 1, 1};

    bool         outdated = true;
    Matrix<4, 4> transformationMatrix {};

    public:
    ComplexGameObject(const Vector<3>& position={}, const Vector<3>& rotation={}, const Vector<3>& scale={1,1,1});

    Matrix<4, 4>& getTransformationMatrix();

    void          setOutdated();

    Vector<3>&    getPosition();
    Vector<3>&    getRotation();
    Vector<3>&    getScale();
    void          setPosition(const Vector<3>& position);
    void          setRotation(const Vector<3>& rotation);
    void          setScale(const Vector<3>& scale);

    protected:
    virtual void dataChangedNotification() {};

    private:
    void updateTransformationMatrix();
};

#endif    // ENGINE3D_COMPONENT_COMPLEXGAMEOBJECT_H_
