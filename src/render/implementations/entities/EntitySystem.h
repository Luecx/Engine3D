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
    RawModel model{0,0};


    bool addElement(RawModel& element) override {
        return false;
    }
    bool removeElement(RawModel& element) override {
        return false;
    }
    void render(Camera& camera) override {
        shader.start();
        shader.loadVPMatrix(camera.getViewMatrix(), camera.getProjectionMatrix());
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);
        glDisable(GL_CULL_FACE);

        glBindVertexArray(model.vaoID);
        glDrawElements(GL_TRIANGLES, model.vertexCount, GL_UNSIGNED_INT, nullptr);
        shader.stop();
    }
};

#endif    // ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSYSTEM_H_
