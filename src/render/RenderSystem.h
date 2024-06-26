//
// Created by Luecx on 01.06.2021.
//

#ifndef ENGINE3D_SRC_RENDER_RENDERSYSTEM_H_
#define ENGINE3D_SRC_RENDER_RENDERSYSTEM_H_

#include "../camera/Camera.h"
#include "../ecs/ecs.h"

template<typename Shader>
class RenderSystem : public ecs::System {

    protected:
    Shader shader {};

    public:
    void enable() {
        shader.createShader();
    }
    bool isEnabled() {
        return shader.isCreated();
    }
    void destroy() override {
        GL_ERROR_CHECK();
        shader.destroy();
        GL_ERROR_CHECK();
    }

    virtual void render(ecs::ECS* ecs) = 0;
};

#endif    // ENGINE3D_SRC_RENDER_RENDERSYSTEM_H_
