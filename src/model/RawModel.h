//
// Created by Luecx on 31.05.2021.
//

#ifndef ENGINE3D_SRC_MODEL_RAWMODEL_H_
#define ENGINE3D_SRC_MODEL_RAWMODEL_H_

#include "../glad.h"

#include <iostream>
class RawModel {

    public:
    GLuint vaoID;
    int    vertexCount;

    private:
    bool cleanUp = false;

    public:
    RawModel();
    RawModel(GLuint vao_id, int vertex_count);
    RawModel(const RawModel& other);
    RawModel(RawModel&& other);
    RawModel& operator=(const RawModel& other);
    RawModel& operator=(RawModel&& other);
    virtual ~RawModel();

    private:
    void clean();
};

#endif    // ENGINE3D_SRC_MODEL_RAWMODEL_H_
