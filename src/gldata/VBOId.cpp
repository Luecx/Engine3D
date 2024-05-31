//
// Created by finn on 5/22/24.
//

#include "VBOId.h"

#include "../core/glerror.h"

VBOId::VBOId() {
    glGenBuffers(1, &data_id);
    GL_ERROR_CHECK();
    std::cout << "VBOId created: " << data_id << std::endl;
}

VBOId::~VBOId() {
//    std::cout << "VBOId destroyed: " << data_id << std::endl;
//    if (data_id != 0)
//        glDeleteBuffers(1, &data_id);
}

void VBOId::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, data_id);
    GL_ERROR_CHECK();
}

void VBOId::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GL_ERROR_CHECK();
}

void VBOId::store_data(int attributeNumber, int dimensions, std::vector<float>& data) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), &data.front(), GL_STATIC_DRAW);
    GL_ERROR_CHECK();
    glVertexAttribPointer(attributeNumber, dimensions, GL_FLOAT, GL_FALSE, dimensions * sizeof(float), nullptr);
    GL_ERROR_CHECK();
    unbind();
}

void VBOId::store_data(int attributeNumber, int dimensions, std::vector<int>& data) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(int) * data.size(), &data.front(), GL_STATIC_DRAW);
    GL_ERROR_CHECK();
    glVertexAttribPointer(attributeNumber, dimensions, GL_INT, GL_FALSE, 0, nullptr);
    GL_ERROR_CHECK();
    unbind();
}

void VBOId::store_indices(std::vector<int>& indices) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data_id);
    GL_ERROR_CHECK();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices.front(), GL_STATIC_DRAW);
    GL_ERROR_CHECK();
    unbind();
}