//
// Created by Luecx on 31.05.2021.
//

#include "RawModel.h"

RawModel::RawModel() : vaoID(0), vertexCount(0), cleanUp(false) {
}
RawModel::RawModel(GLuint vao_id, int vertex_count) : vaoID(vao_id), vertexCount(vertex_count), cleanUp(true) {
}
RawModel::RawModel(const RawModel& other) : vaoID(other.vaoID), vertexCount(other.vertexCount), cleanUp(false) {
}
RawModel::RawModel(RawModel&& other) : vaoID(other.vaoID), vertexCount(other.vertexCount), cleanUp(other.cleanUp) {
    other.cleanUp = false;
}
RawModel& RawModel::operator=(const RawModel& other) {
    clean();
    this->vaoID       = other.vaoID;
    this->vertexCount = other.vertexCount;
    this->cleanUp     = false;
    return *this;
}
RawModel& RawModel::operator=(RawModel&& other) {
    clean();
    this->cleanUp     = other.cleanUp;
    this->vaoID       = other.vaoID;
    this->vertexCount = other.vertexCount;
    other.cleanUp     = false;
    return *this;
}
RawModel::~RawModel() {
    clean();
}
void RawModel::clean() {
    if (cleanUp && false) {
        std::cout << "delete vao, id=" << vaoID << std::endl;
        GLint nAttr = 0;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nAttr);
        glBindVertexArray(vaoID);
        for (int iAttr = 0; iAttr < nAttr; ++iAttr) {
            GLint vboId = 0;
            glGetVertexAttribiv(iAttr, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &vboId);
            if (vboId > 0) {
                glDeleteBuffers(1, reinterpret_cast<const GLuint*>(&vboId));
            }
        }
        cleanUp = false;
    }
}
