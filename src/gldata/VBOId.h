//
// Created by finn on 5/22/24.
//

#ifndef ENGINE3D_VBOID_H
#define ENGINE3D_VBOID_H

#include "GLData.h"

#include <vector>
#include <memory>

class VBOId : public GLData {

    public:
    VBOId();
    ~VBOId();


    public:
    void bind() override;
    void unbind() override;

    void store_data(int attributeNumber, int dimensions, std::vector<float>& data);
    void store_data(int attributeNumber, int dimensions, std::vector<int>& data);
    void store_indices(std::vector<int>& indices);

};

using VBOIdPtr = std::shared_ptr<VBOId>;

#endif    // ENGINE3D_VBOID_H
