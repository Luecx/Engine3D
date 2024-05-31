//
// Created by Luecx on 31.05.2021.
//

#ifndef ENGINE3D_SRC_MODEL_RAWMODEL_H_
#define ENGINE3D_SRC_MODEL_RAWMODEL_H_

#include "../glad.h"
#include "../gldata/VAOId.h"

#include "Resource.h"

#include <iostream>

class RawModel : public Resource{

    public:
    VAOIdPtr vaoID = nullptr;
    int      vertexCount;

    RawModel(const std::string& path = "");

    bool     load() override;
    void     unload() override;
};

using RawModelPtr = std::shared_ptr<RawModel>;

#endif    // ENGINE3D_SRC_MODEL_RAWMODEL_H_
