//
// Created by Luecx on 03.06.2021.
//

#ifndef ENGINE3D_SRC_ENTITIES_ENTITY_H_
#define ENGINE3D_SRC_ENTITIES_ENTITY_H_

#include "../component/GroupableGameObject.h"
#include "TexturedModel.h"
class Entity : public GroupableGameObject {

    public:
    TexturedModel texturedModel{};

};

#endif    // ENGINE3D_SRC_ENTITIES_ENTITY_H_
