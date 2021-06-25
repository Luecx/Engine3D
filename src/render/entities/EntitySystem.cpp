//
// Created by Luecx on 24.06.2021.
//
#include "EntitySystem.h"

#include "../../components/LightSource.h"
#include "../../components/ShadowCaster.h"
#include "../../math/Projection.h"

void EntitySystem::prepareModel(RawModel& rawModel) {
    glBindVertexArray(rawModel.vaoID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
}

void EntitySystem::loadShadowView(ecs::ECS* ecs){

    Matrix<4,4> shadowView{};

    // get the caster
    auto caster = ecs->first<ShadowCaster, ComplexTransformation>();
    if(caster == nullptr){
        // load an empty matrix and set it to false
        shader.loadShadowView(false, shadowView);
    }

    auto cast = caster->get<ShadowCaster>().get();

    // compute view, projection
    Vector<3> pos = caster->get<ComplexTransformation>()->getAbsolutePosition();
    Vector<3> target = {};
    Matrix<4,4> view = lookAt(pos, target, {0,1,0});
    Matrix<4,4> proj = orthogonal(-cast.radius,
                                   cast.radius,
                                   cast.radius,
                                  -cast.radius,
                                   cast.near,
                                   cast.far);

    // multiply them on the cpu (faster)
    shadowView = proj * view;

    // load it to the shader
    shader.loadShadowView(true, shadowView);
}


void EntitySystem::prepareTextures(ecs::Entity* entity) {
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
    } else {
        shader.loadParallaxDepth(0);
    }

    shader.loadMaterialMapUsage(hasNormal, hasSpecular);
}
void EntitySystem::prepareMaterial(ecs::Entity* entity) {
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
void EntitySystem::prepareLights(Camera* camera, ecs::ECS* ecs) {
    std::vector<std::tuple<LightSource*, Vector<3>, float>> lights {};
    for (auto& entity : ecs->each<LightSource, ComplexTransformation>()) {

        LightSource* source                                            = entity->get<LightSource>().operator->();
        Vector<3>                                        lightPosition = entity->get<ComplexTransformation>()->getAbsolutePosition();
        lights.push_back({source, lightPosition, (lightPosition - camera->getAbsolutePosition()).length()});
    }

    // sort if too many lights
    if (lights.size() >= MAX_LIGHTS) {
        std::sort(lights.begin(), lights.end(),
                  [](std::tuple<LightSource*, Vector<3>, float> s1, std::tuple<LightSource*, Vector<3>, float> s2) {
                      return (std::get<2>(s1) > std::get<2>(s2));
                  });
    }

    // get the amount of lights we can use
    int lightCount = std::min(MAX_LIGHTS, (int) lights.size());

    // load the amount of lights to use
    shader.loadLightCount(lightCount);

    // load the light data
    for (int i = 0; i < lightCount; i++) {
        LightSource* source        = std::get<0>(lights[i]);
        Vector<3>    lightLocation = std::get<1>(lights[i]);
        shader.loadLight(i, lightLocation, source->color, source->falloff);
    }
}
void EntitySystem::render(ecs::ECS* ecs) {

    Camera* camera = ecs->first<Camera*>()->get<Camera*>().get();
    if (camera == nullptr)
        return;

    shader.start();

    // loading view and projection matrix
    shader.loadVPMatrix(camera->getViewMatrix(), camera->getProjectionMatrix());
    shader.loadCameraPosition(camera->getAbsolutePosition());

    // load shadow stuff
    loadShadowView(ecs);

    // load the light sources
    prepareLights(camera, ecs);

    // load the shadow maps
    loadShadowMaps(ecs);

    // enabling culling
    glEnable(GL_CULL_FACE);

    // enabling depth testing
    glEnable(GL_DEPTH_TEST);

    for (auto& entity : ecs->each<ComplexTransformation, RawModel, ColorMap>()) {

        prepareModel(entity->get<RawModel>().get());
        prepareTextures(entity);
        prepareMaterial(entity);

        shader.loadTransformationMatrix(entity->get<ComplexTransformation>()->getAbsoluteTransformationMatrix());

        glDrawElements(GL_TRIANGLES, entity->get<RawModel>()->vertexCount, GL_UNSIGNED_INT, nullptr);
    }

    shader.stop();
}
void EntitySystem::process(ecs::ECS* ecs, [[maybe_unused]] double delta) {
    render(ecs);
}
void EntitySystem::loadShadowMaps(ecs::ECS* ecs) {
    ecs::Entity* c = ecs->first<ShadowCaster>();
    if (c == nullptr)
        return;
    ShadowCaster& caster = c->get<ShadowCaster>().get();
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, caster.frameBuffer.attachments[0]);
}
