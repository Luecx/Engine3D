//
// Created by Luecx on 24.06.2021.
//

#include "ShadowSystem.h"

#include "../../components/ShadowCaster.h"
#include "../../core/config.h"
#include "../../math/Projection.h"

#include <GLFW/glfw3.h>

void prepareModel(RawModel& rawModel) {
    rawModel.vaoID->bind();
    glEnableVertexAttribArray(0);
}
void ShadowSystem::process(ecs::ECS* ecs, double delta) {
    render(ecs);
}
void ShadowSystem::render(ecs::ECS* ecs) {

    // adjust the viewport
    glViewport(0, 0, SHADOW_RESOLUTION, SHADOW_RESOLUTION);

    shader.start();
    // go over all casters
    int casters = 0;

    //    glCullFace(GL_FRONT);

    for (ecs::Entity* caster : ecs->each<ComplexTransformation, ShadowCaster>()) {
        // bind shadow frame buffer
        if (casters >= MAX_SHADOWS)
            break;

        // get the shadow caster
        ShadowCaster& cast = caster->get<ShadowCaster>().get();

        // enable the fbo
        cast.frameBuffer.bind();

        // clear the depth
        glClear(GL_DEPTH_BUFFER_BIT);

        // load view * projection
        Vector<3>    pos    = caster->get<ComplexTransformation>()->getAbsolutePosition();
        Vector<3>    target = {};
        Matrix<4, 4> view   = lookAt(pos, target, {0, 1, 0});
        Matrix<4, 4> proj   = orthogonal(-cast.radius, cast.radius, cast.radius, -cast.radius, cast.near, cast.far);

        // view * projection stored inside the entity
        cast.shadow_view = proj * view;

        // load the view projection matrix
        shader.loadVPMatrix(view, proj);

        // iterate over all the entities and render
        for (ecs::Entity* entity : ecs->each<ComplexTransformation, RawModelPtr>()) {
            prepareModel(*entity->get<RawModelPtr>().get());
            shader.loadTransformationMatrix(entity->get<ComplexTransformation>()->getAbsoluteTransformationMatrix());
            glDrawElements(GL_TRIANGLES, entity->get<RawModelPtr>().get()->vertexCount, GL_UNSIGNED_INT, nullptr);
        }

        // unbind the framebuffer
        cast.frameBuffer.unbind(ecs->first<GLFWwindow*>()->get<GLFWwindow*>().get());

        // increase the amount of counted casters
        casters++;
    }
    //    glCullFace(GL_BACK);
    shader.stop();
}
