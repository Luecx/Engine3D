//
// Created by Luecx on 01.06.2021.
//
#include "VAOLoader.h"

#include <iostream>

GLuint createVAO() {
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    return vaoID;
}
void unbindVAO() {
    glBindVertexArray(0);
}
void bindIndicesBuffer(std::vector<int> indices) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);

}
GLuint storeDataInAttributeList(int attributeNumber, int dimensions, std::vector<float>& data) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), &data.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, dimensions, GL_FLOAT, GL_FALSE, dimensions * sizeof(float), nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vboID;
}
GLuint storeDataInAttributeList(int attributeNumber, int dimensions, std::vector<int>& data) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int) * data.size(), &data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, dimensions, GL_INT, false, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vboID;
}

RawModel loadToVao(std::vector<float>& positions, std::vector<float>& textureCoords,
                   std::vector<float>& normals, std::vector<int>& indices) {
    GLuint vaoID = createVAO();

    storeDataInAttributeList(0, 3, positions);
    storeDataInAttributeList(1, 2, textureCoords);
    storeDataInAttributeList(2, 3, normals);
    bindIndicesBuffer(indices);
    unbindVAO();
    return RawModel {vaoID, (int) indices.size()};
}
RawModel loadToVao(std::vector<float>& positions, std::vector<float>& textureCoords,
                   std::vector<float>& normals, std::vector<float>& tangents,
                   std::vector<int>& indices) {
    GLuint vaoID = createVAO();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(0, 3, positions);
    storeDataInAttributeList(1, 2, textureCoords);
    storeDataInAttributeList(2, 3, normals);
    storeDataInAttributeList(3, 3, tangents);
    unbindVAO();
    return RawModel {vaoID, (int) indices.size()};
}
RawModel loadToVao(std::vector<float>& positions, std::vector<int>& indices) {
    GLuint vaoID = createVAO();
    storeDataInAttributeList(0, 3, positions);
    bindIndicesBuffer(indices);
    unbindVAO();
    return RawModel {vaoID,(int) indices.size()};
}
RawModel loadToVao2D(std::vector<float>& positions, std::vector<float>& textureCoords) {
    GLuint vaoID = createVAO();
    storeDataInAttributeList(0, 2, positions);
    storeDataInAttributeList(1, 2, textureCoords);
    unbindVAO();
    return RawModel {vaoID,(int) positions.size()};

}
