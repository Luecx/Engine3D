//
// Created by Luecx on 02.06.2021.
//

#ifndef ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSYSTEM_H_
#define ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSYSTEM_H_

#include "../../../model/RawModel.h"
#include "../../RenderSystem.h"
#include "EntityShader.h"

class EntitySystem : public RenderSystem<EntityShader, Entity> {

    std::unordered_map<int, std::vector<Entity*>> entities {};

    public:
    bool addElement(Entity* element) override {
        int hash = element->texturedModel.material.colorMap.getTextureId() * 8192 + element->texturedModel.rawModel.vaoID;
        if (entities.find(hash) == entities.end()) {
            entities[hash] = {};
            entities[hash].emplace_back(element);
        } else {
            entities[hash].emplace_back(element);
        }
        return true;
    }
    bool removeElement(Entity* element) override {
        return true;
    }

    void prepareTexturedModel(TexturedModel& model) {
        glBindVertexArray(model.rawModel.vaoID);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, model.material.colorMap.getTextureId());
    };

    void render(Camera& camera) override {
        shader.start();
        // loading view and projection matrix
        shader.loadVPMatrix(camera.getViewMatrix(), camera.getProjectionMatrix());

        // enabling culling
        glEnable(GL_CULL_FACE);

        // enabling depth testing
        glEnable(GL_DEPTH_TEST);

        for (auto& pair : entities) {

            if (pair.second.size() == 0) {
                continue;
            }

            prepareTexturedModel(pair.second.at(0)->texturedModel);

            for (Entity* e : pair.second) {
                shader.loadTransformationMatrix(e->getAbsoluteTransformationMatrix());

                glDrawElements(GL_TRIANGLES, e->texturedModel.rawModel.vertexCount, GL_UNSIGNED_INT, nullptr);
            }
        }

        shader.stop();
    }
};

#endif    // ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSYSTEM_H_
