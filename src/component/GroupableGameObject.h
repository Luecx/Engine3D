//
// Created by Luecx on 31.05.2021.
//

#ifndef ENGINE3D_COMPONENT_GROUPABLEGAMEOBJECT_H_
#define ENGINE3D_COMPONENT_GROUPABLEGAMEOBJECT_H_

#include "ComplexGameObject.h"
class GroupableGameObject : public ComplexGameObject {

    private:
    GroupableGameObject*              parent = nullptr;
    std::vector<GroupableGameObject*> childs {};

    Matrix<4, 4>                      absoluteTransformationMatrix {};
    Vector<3>                         absolutePosition {};

    bool                              absoluteOutdated = true;

    public:
    GroupableGameObject(const Vector<3>& position = {}, const Vector<3>& rotation = {},
                        const Vector<3>& scale = {1, 1, 1});

    Matrix<4, 4>&                     getAbsoluteTransformationMatrix();

    Vector<3>&                        getAbsolutePosition();

    void                              setAbsoluteOutdated();

    bool                              hasParent();

    bool                              setParent(GroupableGameObject* parent);

    bool                              removeParent();

    bool                              addChild(GroupableGameObject* child);

    bool                              removeChild(GroupableGameObject* child);

    std::vector<GroupableGameObject*> getChilds();

    protected:
    virtual void absoluteDataChangedNotification() {};

    void         dataChangedNotification() override;

    private:
    void updateAbsoluteTransformationMatrix();
};

#endif    // ENGINE3D_COMPONENT_GROUPABLEGAMEOBJECT_H_
