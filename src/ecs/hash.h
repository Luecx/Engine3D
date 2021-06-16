//
// Created by Luecx on 15.06.2021.
//

#ifndef ECS_ECS_HASH_H_
#define ECS_ECS_HASH_H_

#include "types.h"
namespace ecs {

template<typename Component> Hash getComponentHash() { return std::type_index(typeid(Component)); }
}    // namespace ecs

#endif    // ECS_ECS_HASH_H_
