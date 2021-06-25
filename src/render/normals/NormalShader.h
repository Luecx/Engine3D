//
// Created by Luecx on 02.06.2021.
//

#ifndef ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_NORMALS_NORMALSHADER_H_
#define ENGINE3D_SRC_RENDER_IMPLEMENTATIONS__NORMALS_NORMALSHADER_H_

#include "../../material/NormalMap.h"
#include "../ShaderProgram.h"

#define MAX_LIGHTS_ENTITY_SHADER 4

class NormalShader : public ShaderProgram {

    private:
    int loc_transformationMatrix;
    int loc_viewMatrix;
    int loc_projectionMatrix;


    public:
    NormalShader() : ShaderProgram(
            R"(C:\Users\Luecx\CLionProjects\Engine3D\src\render\normals\vs.glsl)",
            R"(C:\Users\Luecx\CLionProjects\Engine3D\src\render\normals\fs.glsl)",
            R"(C:\Users\Luecx\CLionProjects\Engine3D\src\render\normals\gs.glsl)") {
    }

    protected:
    void getAllUniformLocations() override {
        ShaderProgram::getAllUniformLocations();
        loc_transformationMatrix = ShaderProgram::getUniformLocation("transformationMatrix");
        loc_viewMatrix           = ShaderProgram::getUniformLocation("viewMatrix");
        loc_projectionMatrix     = ShaderProgram::getUniformLocation("projectionMatrix");
    }
    void bindAttributes() override {
        ShaderProgram::bindAttributes();
    }
    void connectAllTextureUnits() override {
        ShaderProgram::connectAllTextureUnits();
    }
    public:
    void loadTransformationMatrix(Matrix<4,4> &transformationMatrix){
        loadMatrix(loc_transformationMatrix, transformationMatrix);
    }
    void loadVPMatrix(Matrix<4,4> &viewMatrix,Matrix<4,4> &projectionMatrix){
        loadMatrix(loc_viewMatrix, viewMatrix);
        loadMatrix(loc_projectionMatrix, projectionMatrix);
    }

};

#endif    // ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSHADER_H_
