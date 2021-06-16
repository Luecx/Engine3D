//
// Created by Luecx on 31.05.2021.
//

#ifndef ENGINE3D_COMPONENT_GROUPABLEGAMEOBJECT_H_
#define ENGINE3D_COMPONENT_GROUPABLEGAMEOBJECT_H_

#include "Transformation.h"
class ComplexTransformation : public Transformation {

    private:
    ComplexTransformation*              parent = nullptr;
    std::vector<ComplexTransformation*> childs {};

    Matrix<4, 4>                      absoluteTransformationMatrix {};
    Vector<3>                         absolutePosition {};

    bool                              absoluteOutdated = true;

    public:
    ComplexTransformation(const Vector<3>& position = {}, const Vector<3>& rotation = {},
                        const Vector<3>& scale = {1, 1, 1});

    virtual ~ComplexTransformation();

    Matrix<4, 4>&                     getAbsoluteTransformationMatrix();

    Vector<3>&                        getAbsolutePosition();

    void                              setAbsoluteOutdated();

    bool                              hasParent();

    bool                              setParent(ComplexTransformation* parent);

    bool                              removeParent();

    bool                              addChild(ComplexTransformation* child);

    bool                              removeChild(ComplexTransformation* child);

    std::vector<ComplexTransformation*> getChilds();

    protected:
    virtual void absoluteDataChangedNotification() {};

    void         dataChangedNotification() override;

    private:
    void updateAbsoluteTransformationMatrix();
};

#endif    // ENGINE3D_COMPONENT_GROUPABLEGAMEOBJECT_H_
