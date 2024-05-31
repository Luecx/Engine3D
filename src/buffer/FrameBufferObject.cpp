//
// Created by Luecx on 25.06.2021.
//

#include "FrameBufferObject.h"
FrameBufferObject::FrameBufferObject() {
    cleanUp = false;
}
FrameBufferObject::FrameBufferObject(int width, int height)
    : width(width)
    , height(height) {
    // generating the frame buffer
    glGenFramebuffers(1, &fbo);
    GL_ERROR_CHECK();
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    GL_ERROR_CHECK();
    glDrawBuffer(GL_NONE);
    GL_ERROR_CHECK();
    glReadBuffer(GL_NONE);
    GL_ERROR_CHECK();
    this->cleanUp = true;
}
FrameBufferObject::FrameBufferObject(FrameBufferObject&& other) noexcept {
    this->width       = other.width;
    this->height      = other.height;
    this->fbo         = other.fbo;
    this->attachments = other.attachments;

    this->cleanUp     = other.cleanUp;
    other.cleanUp     = false;
}
FrameBufferObject::FrameBufferObject(const FrameBufferObject& other) {
    this->width       = other.width;
    this->height      = other.height;
    this->fbo         = other.fbo;
    this->attachments = other.attachments;

    this->cleanUp     = false;
}
FrameBufferObject& FrameBufferObject::operator=(FrameBufferObject&& other) {
    clean();

    this->width       = other.width;
    this->height      = other.height;
    this->fbo         = other.fbo;
    this->attachments = other.attachments;

    this->cleanUp     = other.cleanUp;
    other.cleanUp     = false;
    return *this;
}
FrameBufferObject& FrameBufferObject::operator=(const FrameBufferObject& other) {
    clean();

    this->width       = other.width;
    this->height      = other.height;
    this->fbo         = other.fbo;
    this->attachments = other.attachments;
    this->cleanUp     = false;
    return *this;
}

void FrameBufferObject::bind() {
    glBindTexture(GL_TEXTURE_2D, 0);
    GL_ERROR_CHECK();
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
    GL_ERROR_CHECK();
    glViewport(0, 0, width, height);
    GL_ERROR_CHECK();
}
void FrameBufferObject::unbind(GLFWwindow* window) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    GL_ERROR_CHECK();
    glBindTexture(GL_TEXTURE_2D, 0);
    GL_ERROR_CHECK();
    int newWidth, newHeight;
    glfwGetWindowSize(window, &newWidth, &newHeight);
    glViewport(0, 0, newWidth, newHeight);
    GL_ERROR_CHECK();
}
unsigned int FrameBufferObject::createDepthBufferAttachment(int width, int height) {
    unsigned int texture;
    glGenTextures(1, &texture);
    GL_ERROR_CHECK();
    glBindTexture(GL_TEXTURE_2D, texture);
    GL_ERROR_CHECK();
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_DEPTH_COMPONENT16,
                 width,
                 height,
                 0,
                 GL_DEPTH_COMPONENT,
                 GL_FLOAT,
                 NULL);
    GL_ERROR_CHECK();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    GL_ERROR_CHECK();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GL_ERROR_CHECK();
    float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    GL_ERROR_CHECK();

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
    GL_ERROR_CHECK();
    attachments.push_back(texture);
    return texture;
}

void FrameBufferObject::clean() {
    if (cleanUp) {
        glDeleteFramebuffers(1, &fbo);
        for (auto h : attachments) {
            glDeleteTextures(1, &h);
            GL_ERROR_CHECK();
        }
    }
    GL_ERROR_CHECK();
    cleanUp = false;
}
