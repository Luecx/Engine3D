//
// Created by Luecx on 25.06.2021.
//

#ifndef ENGINE3D_SRC_BUFFER_FRAMEBUFFEROBJECT_H_
#define ENGINE3D_SRC_BUFFER_FRAMEBUFFEROBJECT_H_

#include "../core/glerror.h"
#include "../glad.h"

#include <GLFW/glfw3.h>
#include <vector>
struct FrameBufferObject {

    public:
    int                       width;
    int                       height;
    unsigned int              fbo;
    std::vector<unsigned int> attachments {};

    private:
    bool cleanUp = false;

    public:
    FrameBufferObject();
    FrameBufferObject(int width, int height);
    virtual ~FrameBufferObject() {
        if (cleanUp) {
            glDeleteFramebuffers(1, &fbo);
            GL_ERROR_CHECK();
            for (auto h : attachments) {
                glDeleteTextures(1, &h);
            }
        }
    }

    FrameBufferObject(FrameBufferObject&& other) noexcept;
    FrameBufferObject(const FrameBufferObject& other);
    FrameBufferObject& operator=(FrameBufferObject&& other);
    FrameBufferObject& operator=(const FrameBufferObject& other);

    private:
    void clean();

    public:
    void         bind();
    void         unbind(GLFWwindow* window);
    unsigned int createDepthBufferAttachment(int width, int height);
};

#endif    // ENGINE3D_SRC_BUFFER_FRAMEBUFFEROBJECT_H_
