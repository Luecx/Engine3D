//
// Created by Luecx on 24.06.2021.
//

#ifndef ENGINE3D_SRC_RENDER_SHADOW_SHADOWSYSTEM_H_
#define ENGINE3D_SRC_RENDER_SHADOW_SHADOWSYSTEM_H_

#include "../../ecs/system.h"
#include "../../model/RawModel.h"
#include "../RenderSystem.h"
#include "ShadowShader.h"

class ShadowSystem : public RenderSystem<ShadowShader>, public ecs::System{
    private:
    void prepareModel(RawModel& rawModel);
    public:
    void process(ecs::ECS* ecs, double delta) override;
    void render(ecs::ECS* ecs) override;
};

#endif    // ENGINE3D_SRC_RENDER_SHADOW_SHADOWSYSTEM_H_
