//
// Created by Luecx on 02.06.2021.
//

#ifndef ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_NORMALS_NORMALSYSTEM_H_
#define ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_NORMALS_NORMALSYSTEM_H_

#include "../../material/LightReflection.h"
#include "../../material/MaterialMap.h"
//#include "../../material/SpecularMap.h"
#include "../../material/TextureStretch.h"
#include "../../resources/RawModel.h"
#include "../RenderSystem.h"
#include "NormalShader.h"

struct DisplayNormal {};

class NormalSystem : public RenderSystem<NormalShader> {

    public:
    void prepareModel(RawModel& rawModel) {
        rawModel.vaoID->bind();
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glEnableVertexAttribArray(3);
    };

    void render(ecs::ECS* ecs) override {

//        Camera* camera = ecs->first<Camera*>()->get<Camera*>().get();
//        if (camera == nullptr)
//            return;
//
//        shader.start();
//        // loading view and projection matrix
//        shader.loadVPMatrix(camera->getViewMatrix(), camera->getProjectionMatrix());
//
//        // enabling culling
//        glEnable(GL_CULL_FACE);
//
//        // enabling depth testing
//        glEnable(GL_DEPTH_TEST);
//
//        for (auto& entity : ecs->each<ComplexTransformation, RawModel, DisplayNormal>()) {
//
//            prepareModel(entity->get<RawModel>().get());
//
//            shader.loadTransformationMatrix(
//                entity->get<ComplexTransformation>()->getAbsoluteTransformationMatrix());
//
//            glDrawElements(GL_TRIANGLES,
//                           entity->get<RawModel>()->vertexCount,
//                           GL_UNSIGNED_INT,
//                           nullptr);
//        }
//
//        shader.stop();
    }

    void process(ecs::ECS* ecs, [[maybe_unused]] double delta) override {
        render(ecs);
    }
};

#endif    // ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSYSTEM_H_
