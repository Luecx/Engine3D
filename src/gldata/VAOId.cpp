//
// Created by finn on 5/22/24.
//

#include "VAOId.h"

#include "../core/glerror.h"

#include <iostream>

VAOId::VAOId() {
    glGenVertexArrays(1, &data_id);
    GL_ERROR_CHECK();
    std::cout << "VAOId created: " << data_id << std::endl;
}

VAOId::~VAOId() {
//    glBindVertexArray(0);
//    std::cout << "VAOId destroyed: " << data_id << std::endl;
//    GL_ERROR_CHECK();
//    if (data_id != 0) {
//        glDeleteVertexArrays(1, &data_id);
//        GL_ERROR_CHECK();
//    }
//    std::cout << "finished" << std::endl;
}

void VAOId::bind() {
    glBindVertexArray(data_id);
    GL_ERROR_CHECK();
}
void VAOId::unbind() {
    glBindVertexArray(0);
    GL_ERROR_CHECK();
}

void VAOId::addVBO(const VBOIdPtr& vbo) {
    vbos.push_back(vbo);
}
