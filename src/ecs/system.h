//
// Created by Luecx on 15.06.2021.
//

#ifndef ECS_ECS_SYSTEM_H_
#define ECS_ECS_SYSTEM_H_

#include "types.h"
namespace ecs {

struct System {
    virtual void process(ECS* ecs, double delta) = 0;
    virtual void destroy() {};
};

}  // namespace ecs

#endif    // ECS_ECS_SYSTEM_H_
