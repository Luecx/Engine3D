//
// Created by Luecx on 23.06.2021.
//

#ifndef ENGINE3D_SRC_CONTROL_CONTROLSYSTEM_H_
#define ENGINE3D_SRC_CONTROL_CONTROLSYSTEM_H_

#include "../ecs/core.h"

struct SimpleControl{

    float forwardSpeed = 0.4;
    float sideSpeed = 0.4;
    float rotationSpeed = 60;

};

struct ControlSystem : public ecs::System{
    void process(ecs::ECS* ecs, double delta) override;

};

#endif    // ENGINE3D_SRC_CONTROL_CONTROLSYSTEM_H_
