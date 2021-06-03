//
// Created by Luecx on 01.06.2021.
//

#ifndef ENGINE3D_SRC_LOADER_VAOLOADER_H_
#define ENGINE3D_SRC_LOADER_VAOLOADER_H_

#define GLFW_INCLUDE_NONE
#include "../glad.h"
#include "../model/RawModel.h"

#include <vector>



RawModel loadToVao(std::vector<float>& positions, std::vector<float>& textureCoords,
                          std::vector<float>& normals, std::vector<int>& indices);
RawModel loadToVao(std::vector<float>& positions, std::vector<float>& textureCoords,
                          std::vector<float>& normals, std::vector<float>& tangents,
                          std::vector<int>& indices);
RawModel loadToVao(std::vector<float>& positions, std::vector<int>& indices);
RawModel loadToVao2D(float* positions, float* textureCoords);

#endif    // ENGINE3D_SRC_LOADER_VAOLOADER_H_
