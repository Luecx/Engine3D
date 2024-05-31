//
// Created by Luecx on 02.06.2021.
//

#ifndef ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSYSTEM_H_
#define ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSYSTEM_H_

#include "../../material/LightReflection.h"
#include "../../material/MaterialMap.h"
#include "../../material/TextureStretch.h"
#include "../../resources/RawModel.h"
#include "../RenderSystem.h"
#include "EntityShader.h"

class EntitySystem : public RenderSystem<EntityShader> {

    public:
    bool prepareModel(RawModel& rawModel);
    void loadShadowView(ecs::ECS* ecs);
    bool prepareTextures(ecs::Entity* entity);
    void prepareMaterial(ecs::Entity* entity);
    void prepareLights(Camera* camera, ecs::ECS* ecs);
    void loadShadowMaps(ecs::ECS* p_ecs);
    void render(ecs::ECS* ecs) override;
    void process(ecs::ECS* ecs, double delta) override;
};

#endif    // ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSYSTEM_H_
