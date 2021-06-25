//
// Created by Luecx on 24.06.2021.
//

#ifndef ENGINE3D_SRC_RENDER_SHADOW_SHADOWSHADER_H_
#define ENGINE3D_SRC_RENDER_SHADOW_SHADOWSHADER_H_

#include "../ShaderProgram.h"
class ShadowShader : public ShaderProgram {

    int loc_transformationMatrix;
    int loc_viewMatrix;
    int loc_projectionMatrix;

    public:
    ShadowShader();

    void loadTransformationMatrix(Matrix<4,4> &transformationMatrix);
    void loadVPMatrix(Matrix<4,4> &viewMatrix,Matrix<4,4> &projectionMatrix);
    protected:
    void getAllUniformLocations() override;
    void bindAttributes() override;
    void connectAllTextureUnits() override;
};

#endif    // ENGINE3D_SRC_RENDER_SHADOW_SHADOWSHADER_H_
