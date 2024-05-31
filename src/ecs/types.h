//
// Created by Luecx on 15.06.2021.
//

#ifndef ECS_ECS_TYPES_H_
#define ECS_ECS_TYPES_H_

#include <cstdint>
#include <typeindex>

namespace ecs {
struct Entity;
struct ECS;
struct System;
struct ComponentBaseContainer;
template<typename T>
struct ComponentContainer;
template<typename... RTypes>
struct EntityIterator;
template<typename... RTypes>
struct EntitySubSet;

typedef uint32_t        ID;
typedef std::type_index Hash;

#define INVALID_ID ID(-1)

}    // namespace ecs
#endif    // ECS_ECS_TYPES_H_
