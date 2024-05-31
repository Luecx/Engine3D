//
// Created by finn on 5/22/24.
//

#ifndef ENGINE3D_VAOID_H
#define ENGINE3D_VAOID_H

#include "GLData.h"
#include "VBOId.h"

#include <memory>
#include <vector>

class VAOId : public GLData {
    std::vector<VBOIdPtr> vbos;

    public:
    VAOId();
    ~VAOId();

    public:
    void bind() override;
    void unbind() override;

    void addVBO(const VBOIdPtr& vbo);
};

using VAOIdPtr = std::shared_ptr<VAOId>;

#endif    // ENGINE3D_VAOID_H
