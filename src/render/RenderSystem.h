//
// Created by Luecx on 01.06.2021.
//

#ifndef ENGINE3D_SRC_RENDER_RENDERSYSTEM_H_
#define ENGINE3D_SRC_RENDER_RENDERSYSTEM_H_

#include "../camera/Camera.h"
template<typename Shader, typename Element> class RenderSystem {

    protected:
    Shader shader {};

    public:
    void enable() {
        shader.createShader();
    }
    bool isEnabled() {
        return shader.isCreated();
    }

    virtual bool addElement(Element& element)    = 0;
    virtual bool removeElement(Element& element) = 0;
    virtual void render(Camera& camera)          = 0;
};

#endif    // ENGINE3D_SRC_RENDER_RENDERSYSTEM_H_
