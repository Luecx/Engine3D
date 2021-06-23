//
// Created by Luecx on 02.06.2021.
//

#ifndef ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSYSTEM_H_
#define ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSYSTEM_H_

#include "../../../material/ColorMap.h"
#include "../../../material/LightReflection.h"
#include "../../../material/ParallaxMap.h"
#include "../../../material/SpecularMap.h"
#include "../../../material/TextureStretch.h"
#include "../../../model/RawModel.h"
#include "../../RenderSystem.h"
#include "EntityShader.h"

class EntitySystem : public RenderSystem<EntityShader>, public ecs::System {

    public:
    void prepareModel(RawModel& rawModel, ecs::Entity* entity) {
        glBindVertexArray(rawModel.vaoID);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        if (entity->has<NormalMap>()) {
            glEnableVertexAttribArray(3);
        }
    };

    void prepareTextures(ecs::Entity* entity) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, entity->get<ColorMap>()->getTextureId());

        bool hasNormal   = false;
        bool hasSpecular = false;

        if (entity->has<NormalMap>()) {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, entity->get<NormalMap>()->getTextureId());
            hasNormal = true;
        }

        if (entity->has<SpecularMap>()) {
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, entity->get<SpecularMap>()->getTextureId());
            hasSpecular = true;
        }

        if (entity->has<ParallaxMap>()) {
            glActiveTexture(GL_TEXTURE3);
            glBindTexture(GL_TEXTURE_2D, entity->get<ParallaxMap>()->getTextureId());
            shader.loadParallaxDepth(entity->get<ParallaxMap>()->depth);
        }else{
            shader.loadParallaxDepth(0);
        }

        shader.loadMaterialMapUsage(hasNormal, hasSpecular);
    }

    void prepareMaterial(ecs::Entity* entity) {
        if (entity->has<LightReflection>()) {
            LightReflection& ref = entity->get<LightReflection>().get();
            shader.loadMaterialData(ref.shineDamper, ref.reflectivity);
        } else {
            shader.loadMaterialData(1.0f, 0.3f);
        }

        if (entity->has<TextureStretch>()) {
            shader.loadTextureStretch(entity->get<TextureStretch>()->stretch);
        } else {
            shader.loadTextureStretch(1.0f);
        }
    }

    void prepareLights(Camera* camera, ecs::ECS* ecs) {
        std::vector<std::tuple<LightSource*, Vector<3>, float>> lights {};
        for (auto& entity : ecs->each<LightSource, ComplexTransformation>()) {

            LightSource* source                                            = entity->get<LightSource>().operator->();
            Vector<3>                                        lightPosition = entity->get<ComplexTransformation>()->getAbsolutePosition();
            lights.push_back({source, lightPosition, (lightPosition - camera->getAbsolutePosition()).length()});
        }

        // sort if too many lights
        if (lights.size() >= MAX_LIGHTS_ENTITY_SHADER) {
            std::sort(lights.begin(), lights.end(),
                      [](std::tuple<LightSource*, Vector<3>, float> s1, std::tuple<LightSource*, Vector<3>, float> s2) {
                          return (std::get<2>(s1) > std::get<2>(s2));
                      });
        }

        // get the amount of lights we can use
        int lightCount = std::min(MAX_LIGHTS_ENTITY_SHADER, (int) lights.size());

        // load the amount of lights to use
        shader.loadLightCount(lightCount);

        // load the light data
        for (int i = 0; i < lightCount; i++) {
            LightSource* source        = std::get<0>(lights[i]);
            Vector<3>    lightLocation = std::get<1>(lights[i]);
            shader.loadLight(i, lightLocation, source->color, source->falloff);
        }
    }

    void render(ecs::ECS* ecs) override {

        Camera* camera = ecs->first<Camera*>()->get<Camera*>().get();
        if (camera == nullptr)
            return;

        shader.start();
        // loading view and projection matrix
        shader.loadVPMatrix(camera->getViewMatrix(), camera->getProjectionMatrix());
        shader.loadCameraPosition(camera->getAbsolutePosition());

        // load the light sources
        prepareLights(camera, ecs);

        // enabling culling
        glEnable(GL_CULL_FACE);

        // enabling depth testing
        glEnable(GL_DEPTH_TEST);

        for (auto& entity : ecs->each<ComplexTransformation, RawModel, ColorMap>()) {

            prepareModel(entity->get<RawModel>().get(), entity);
            prepareTextures(entity);
            prepareMaterial(entity);

            shader.loadTransformationMatrix(entity->get<ComplexTransformation>()->getAbsoluteTransformationMatrix());

            glDrawElements(GL_TRIANGLES, entity->get<RawModel>()->vertexCount, GL_UNSIGNED_INT, nullptr);
        }

        shader.stop();
    }

    void process(ecs::ECS* ecs, double delta) override {
        render(ecs);
    }
};

#endif    // ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSYSTEM_H_
