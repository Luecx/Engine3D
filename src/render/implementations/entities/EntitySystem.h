//
// Created by Luecx on 02.06.2021.
//

#ifndef ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSYSTEM_H_
#define ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSYSTEM_H_

#include "../../../model/RawModel.h"
#include "../../RenderSystem.h"
#include "EntityShader.h"

class EntitySystem : public RenderSystem<EntityShader> {

    public:

    void prepareTexturedModel(RawModel& rawModel, ColorMap& colorMap) {
        glBindVertexArray(rawModel.vaoID);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, colorMap.getTextureId());
    };

    void prepareLights(ecs::ECS* ecs){
        for (auto& entity : ecs->each<LightSource>()) {

        }
    }

    void render(Camera& camera, ecs::ECS* ecs) override {
        shader.start();
        // loading view and projection matrix
        shader.loadVPMatrix(camera.getViewMatrix(), camera.getProjectionMatrix());

        // enabling culling
        glEnable(GL_CULL_FACE);

        // enabling depth testing
        glEnable(GL_DEPTH_TEST);

        for (auto& entity : ecs->each<ComplexTransformation, RawModel, ColorMap>()) {

            prepareTexturedModel(entity->get<RawModel>().get(), entity->get<ColorMap>().get());

            shader.loadTransformationMatrix(entity->get<ComplexTransformation>()->getAbsoluteTransformationMatrix());

            glDrawElements(GL_TRIANGLES, entity->get<RawModel>()->vertexCount, GL_UNSIGNED_INT, nullptr);

        }

        shader.stop();
    }
};

#endif    // ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSYSTEM_H_
