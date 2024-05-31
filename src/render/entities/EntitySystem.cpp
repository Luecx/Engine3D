//
// Created by Luecx on 24.06.2021.
//
#include "EntitySystem.h"

#include "../../components/LightSource.h"
#include "../../components/ShadowCaster.h"
#include "../../math/Projection.h"

bool EntitySystem::prepareModel(RawModel& rawModel) {

    // check if the model is properly loaded like for the textures
    if (rawModel.loaded &&
        rawModel.vaoID->operator GLuint() != 0) {

        rawModel.vaoID->bind();
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
    } else {
        return false;
    }
    return true;
}

void EntitySystem::loadShadowView(ecs::ECS* ecs) {

    Matrix<4, 4> shadowView {};

    // get the caster
    auto caster = ecs->first<ShadowCaster, ComplexTransformation>();
    if (caster == nullptr) {
        // load an empty matrix and set it to false
        shader.loadShadowView(false, shadowView);
        return;
    }

    auto cast = caster->get<ShadowCaster>().get();

    // load it to the shader
    shader.loadShadowView(true, cast.shadow_view);
}

bool EntitySystem::prepareTextures(ecs::Entity* entity) {

    // bind color map if loaded, otherwise dont load anything
    if (   entity->has<ColorMap>()
        && entity->get<ColorMap>()->map->loaded
        && entity->get<ColorMap>()->map->textureId->operator GLuint() != 0){

        glActiveTexture(GL_TEXTURE0);
        entity->get<ColorMap>()->map.get()->textureId->bind();
    } else {
        return false;
    }

    bool hasNormal   = false;
    bool hasSpecular = false;

    if (   entity->has<NormalMap>()
        && entity->get<NormalMap>()->map->loaded
        && entity->get<NormalMap>()->map->textureId->operator GLuint() != 0){
        glActiveTexture(GL_TEXTURE1);
        entity->get<NormalMap>()->map->textureId->bind();
        hasNormal = true;
    }

    if (   entity->has<SpecularMap>()
        && entity->get<SpecularMap>()->map->loaded
        && entity->get<SpecularMap>()->map->textureId->operator GLuint() != 0){
        glActiveTexture(GL_TEXTURE2);
        entity->get<SpecularMap>()->map->textureId->bind();
        hasNormal = true;
    }

    if (   entity->has<ParallaxMap>()
        && entity->get<ParallaxMap>()->map->loaded
        && entity->get<ParallaxMap>()->map->textureId->operator GLuint() != 0){
        glActiveTexture(GL_TEXTURE3);
        entity->get<ParallaxMap>()->map->textureId->bind();
        shader.loadParallaxDepth(entity->get<ParallaxMap>()->height_scale);
    } else {
        shader.loadParallaxDepth(0);
    }

    shader.loadMaterialMapUsage(hasNormal, hasSpecular);

    return true;
}
void EntitySystem::prepareMaterial(ecs::Entity* entity) {
    if (entity->has<LightReflection>()) {
        LightReflection& ref = entity->get<LightReflection>().get();
        shader.loadMaterialData(ref.shininess);
    } else {
        shader.loadMaterialData(1.0f);
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
        LightSource* source        = entity->get<LightSource>().operator->();
        Vector<3>    lightPosition = entity->get<ComplexTransformation>()->getAbsolutePosition();
        lights.push_back(
            {source, lightPosition, (lightPosition - camera->getAbsolutePosition()).length()});
    }

    // sort if too many lights
    if (lights.size() >= MAX_LIGHTS) {
        std::sort(lights.begin(),
                  lights.end(),
                  [](std::tuple<LightSource*, Vector<3>, float> s1,
                     std::tuple<LightSource*, Vector<3>, float> s2) {
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

    for (auto& entity : ecs->each<ComplexTransformation, RawModelPtr, ColorMap>()) {

        GL_ERROR_CHECK();

        bool model_status = prepareModel(*entity->get<RawModelPtr>().get());
        bool textu_status = prepareTextures(entity);

        GL_ERROR_CHECK();

        prepareMaterial(entity);

        if (!model_status || !textu_status)
            continue;

        shader.loadTransformationMatrix(
            entity->get<ComplexTransformation>()->getAbsoluteTransformationMatrix());

        glDrawElements(GL_TRIANGLES, entity->get<RawModelPtr>()->get()->vertexCount, GL_UNSIGNED_INT, nullptr);
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
