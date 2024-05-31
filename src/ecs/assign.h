//
// Created by Luecx on 16.06.2021.
//

#ifndef ECS_ECS_ASSIGN_H_
#define ECS_ECS_ASSIGN_H_

#include "ecs.h"
#include "entity.h"

namespace ecs {

template<typename T, typename... Args>
inline void Entity::assign(Args&&... args) {
    T t {args...};

    if (has<T>()) {
        ComponentContainer<T> container {t};
        Hash                  hash                                           = getComponentHash<T>();
        reinterpret_cast<ComponentContainer<T>*>(components.at(hash))->get() = t;
    } else {
        auto* container  = new ComponentContainer<T> {t};
        Hash  hash       = getComponentHash<T>();
        components[hash] = container;
        ecs->componentAdded<T>(this);
    }
}
template<typename T>
inline void Entity::remove() {
    if (!has<T>())
        return;
    Hash  hash      = getComponentHash<T>();
    auto* container = components.at(hash);
    // delete container;
    components.erase(hash);
    ecs->componentRemoved<T>(this);
}
inline void Entity::removeAll() {
    for (auto pair : components) {
        ecs->componentRemoved(pair.first, this);
        // delete pair.second;
    }

    components.clear();
}
inline void Entity::destroy() {
    ecs->destroy(this->entityID);
}
}    // namespace ecs

#endif    // ECS_ECS_ASSIGN_H_
