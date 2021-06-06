//
// Created by Luecx on 03.06.2021.
//

#ifndef ENGINE3D_SRC_ENTITIES_ENTITY_H_
#define ENGINE3D_SRC_ENTITIES_ENTITY_H_

#include "../transformation/GroupableGameObject.h"
#include "TexturedModel.h"
#include "components/Component.h"

namespace ecs {


class Entity;

enum ComponentList {
    COLOR_MAP,
    LIGHT_SOURCE,
    SHADOW,

    N_COMPONENTS,
};

class ECS {

    std::vector<Entity> entityList[N_COMPONENTS] {};
};

extern ECS ecs;

class Entity : public GroupableGameObject {

    public:
    Component     components[N_COMPONENTS] {};

    void addComponent()
};
}    // namespace ecs

#endif    // ENGINE3D_SRC_ENTITIES_ENTITY_H_
