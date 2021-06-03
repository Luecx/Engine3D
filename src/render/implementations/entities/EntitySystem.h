//
// Created by Luecx on 02.06.2021.
//

#ifndef ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSYSTEM_H_
#define ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSYSTEM_H_

#include "../../RenderSystem.h"
#include "../../../model/RawModel.h"
#include "EntityShader.h"

class EntitySystem : public RenderSystem<EntityShader, RawModel>{

    public:
    Entity entity{};


    bool addElement(RawModel& element) override {
        return false;
    }
    bool removeElement(RawModel& element) override {
        return false;
    }

    void prepareTexturedModel(TexturedModel& model){
        glBindVertexArray(entity.texturedModel.rawModel.vaoID);
        glEnableVertexAttribArray(0);
    };

    void render(Camera& camera) override {
        shader.start();
        // loading view and projection matrix
        shader.loadVPMatrix(camera.getViewMatrix(), camera.getProjectionMatrix());

        // enabling culling
        glEnable(GL_CULL_FACE);

        // enabling depth testing
        glEnable(GL_DEPTH_TEST);

        prepareTexturedModel(entity.texturedModel);

        glDrawElements(GL_TRIANGLES, entity.texturedModel.rawModel.vertexCount, GL_UNSIGNED_INT, nullptr );

        shader.stop();
    }
};

#endif    // ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSYSTEM_H_
