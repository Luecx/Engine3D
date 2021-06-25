//
// Created by Luecx on 25.06.2021.
//

#include "FrameBufferObject.h"
FrameBufferObject::FrameBufferObject() {
    cleanUp = false;
}
FrameBufferObject::FrameBufferObject(int width, int height) : width(width), height(height) {
    // generating the frame buffer
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
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
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
    glViewport(0, 0, width, height);
}
void FrameBufferObject::unbind(GLFWwindow* window) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    int newWidth, newHeight;
    glfwGetWindowSize(window, &newWidth, &newHeight);
    glViewport(0, 0, newWidth, newHeight);
}
unsigned int FrameBufferObject::createDepthBufferAttachment(int width, int height) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
    attachments.push_back(texture);
    return texture;
}

void FrameBufferObject::clean() {
    if (cleanUp) {
        glDeleteFramebuffers(1, &fbo);
        for (auto h : attachments) {
            glDeleteTextures(1, &h);
        }
    }
    cleanUp = false;
}
