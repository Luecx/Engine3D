#include "VAOLoader.h"

#include "../core/glerror.h"
#include "../gldata/VAOId.h"
#include "../gldata/VBOId.h"

std::tuple<VAOIdPtr, int>  loadToVao(std::vector<float>& positions,
                   std::vector<float>& textureCoords,
                   std::vector<float>& normals,
                   std::vector<int>&   indices) {
    VAOIdPtr vaoID = std::make_shared<VAOId>();
    vaoID->bind();
    GL_ERROR_CHECK();

    // Create VBOs
    VBOIdPtr vboPositions     = std::make_shared<VBOId>();
    VBOIdPtr vboTextureCoords = std::make_shared<VBOId>();
    VBOIdPtr vboNormals       = std::make_shared<VBOId>();
    VBOIdPtr indicesBuffer    = std::make_shared<VBOId>();
    GL_ERROR_CHECK();

    // Store data in VBOs
    vboPositions->store_data(0, 3, positions);
    vboTextureCoords->store_data(1, 2, textureCoords);
    vboNormals->store_data(2, 3, normals);
    indicesBuffer->store_indices(indices);
    GL_ERROR_CHECK();

    // Add VBOs to VAO
    vaoID->addVBO(vboPositions);
    vaoID->addVBO(vboTextureCoords);
    vaoID->addVBO(vboNormals);
    vaoID->addVBO(indicesBuffer);
    GL_ERROR_CHECK();

    vaoID->unbind();
    return std::tuple<VAOIdPtr, int>  {vaoID, static_cast<int>(indices.size())};
}

std::tuple<VAOIdPtr, int>  loadToVao(std::vector<float>& positions,
                   std::vector<float>& textureCoords,
                   std::vector<float>& normals,
                   std::vector<float>& tangents,
                   std::vector<int>&   indices) {
    VAOIdPtr vaoID = std::make_shared<VAOId>();
    vaoID->bind();

    GL_ERROR_CHECK();

    // Create VBOs
    VBOIdPtr vboPositions     = std::make_shared<VBOId>();
    VBOIdPtr vboTextureCoords = std::make_shared<VBOId>();
    VBOIdPtr vboNormals       = std::make_shared<VBOId>();
    VBOIdPtr vboTangents      = std::make_shared<VBOId>();
    VBOIdPtr indicesBuffer    = std::make_shared<VBOId>();

    GL_ERROR_CHECK();
    // Store data in VBOs
    vboPositions->store_data(0, 3, positions);
    vboTextureCoords->store_data(1, 2, textureCoords);
    vboNormals->store_data(2, 3, normals);
    vboTangents->store_data(3, 3, tangents);
    GL_ERROR_CHECK();
    indicesBuffer->store_indices(indices);

    GL_ERROR_CHECK();

    // Add VBOs to VAO
    vaoID->addVBO(vboPositions);
    vaoID->addVBO(vboTextureCoords);
    vaoID->addVBO(vboNormals);
    vaoID->addVBO(vboTangents);
    vaoID->addVBO(indicesBuffer);

    GL_ERROR_CHECK();
    vaoID->unbind();
    return std::tuple<VAOIdPtr, int> {vaoID, static_cast<int>(indices.size())};
}

std::tuple<VAOIdPtr, int>  loadToVao(std::vector<float>& positions, std::vector<int>& indices) {
    VAOIdPtr vaoID = std::make_shared<VAOId>();
    vaoID->bind();

    // Create VBOs
    VBOIdPtr vboPositions  = std::make_shared<VBOId>();
    VBOIdPtr indicesBuffer = std::make_shared<VBOId>();

    // Store data in VBOs
    vboPositions->store_data(0, 3, positions);
    indicesBuffer->store_indices(indices);

    // Add VBOs to VAO
    vaoID->addVBO(vboPositions);
    vaoID->addVBO(indicesBuffer);

    vaoID->unbind();
    return std::tuple<VAOIdPtr, int>  {vaoID, static_cast<int>(indices.size())};
}

std::tuple<VAOIdPtr, int>  loadToVao2D(std::vector<float>& positions, std::vector<float>& textureCoords) {
    VAOIdPtr vaoID = std::make_shared<VAOId>();
    vaoID->bind();

    // Create VBOs
    VBOIdPtr vboPositions     = std::make_shared<VBOId>();
    VBOIdPtr vboTextureCoords = std::make_shared<VBOId>();

    // Store data in VBOs
    vboPositions->store_data(0, 2, positions);
    vboTextureCoords->store_data(1, 2, textureCoords);

    // Add VBOs to VAO
    vaoID->addVBO(vboPositions);
    vaoID->addVBO(vboTextureCoords);

    vaoID->unbind();
    return std::tuple<VAOIdPtr, int>  {vaoID, static_cast<int>(positions.size())};
}
