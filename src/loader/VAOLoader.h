#ifndef VAOLOADER_H
#define VAOLOADER_H

#include "../resources/RawModel.h"

#include <vector>

std::tuple<VAOIdPtr, int>  loadToVao(std::vector<float>& positions, std::vector<float>& textureCoords, std::vector<float>& normals, std::vector<int>& indices);
std::tuple<VAOIdPtr, int>  loadToVao(std::vector<float>& positions, std::vector<float>& textureCoords, std::vector<float>& normals, std::vector<float>& tangents, std::vector<int>& indices);
std::tuple<VAOIdPtr, int>  loadToVao(std::vector<float>& positions, std::vector<int>& indices);
std::tuple<VAOIdPtr, int>  loadToVao2D(std::vector<float>& positions, std::vector<float>& textureCoords);

#endif // VAOLOADER_H
