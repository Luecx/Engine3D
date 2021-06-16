//
// Created by Luecx on 15.06.2021.
//

#ifndef ECS_ECS_COMPONENT_H_
#define ECS_ECS_COMPONENT_H_

#include "types.h"

#include <ostream>
namespace ecs {

struct ComponentBaseContainer {};

template<typename T> struct ComponentContainer : public ComponentBaseContainer {
    T    component;
    bool valid = false;

    explicit ComponentContainer(T& component) : component(component), valid(true) {};

    ComponentContainer() : valid(false) {}

    T*                   operator->() { return &component; }
    T&                   get() { return component; }
    bool                 isValid() { return valid; }

    friend std::ostream& operator<<(std::ostream& os, const ComponentContainer& container) {
        os << container.component;
        return os;
    }
};

}    // namespace ecs

#endif    // ECS_ECS_COMPONENT_H_
