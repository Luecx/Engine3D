//
// Created by Luecx on 02.06.2021.
//

#ifndef ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSHADER_H_
#define ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSHADER_H_

#include "../../ShaderProgram.h"

#define MAX_LIGHTS_ENTITY_SHADER 4

class EntityShader : public ShaderProgram {

    private:

    int               loc_transformationMatrix;
    int               loc_viewMatrix;
    int               loc_projectionMatrix;
    int               loc_lightCount;
    int               loc_lightPosition[MAX_LIGHTS_ENTITY_SHADER];
    int               loc_lightColor   [MAX_LIGHTS_ENTITY_SHADER];
    int               loc_lightFactors [MAX_LIGHTS_ENTITY_SHADER];


    public:
    EntityShader() : ShaderProgram(
            R"(C:\Users\Luecx\CLionProjects\Engine3D\src\render\implementations\entities\vs.glsl)",
            R"(C:\Users\Luecx\CLionProjects\Engine3D\src\render\implementations\entities\fs.glsl)") {
    }

    protected:
    void getAllUniformLocations() override {
        ShaderProgram::getAllUniformLocations();
        loc_transformationMatrix = ShaderProgram::getUniformLocation("transformationMatrix");
        loc_viewMatrix           = ShaderProgram::getUniformLocation("viewMatrix");
        loc_projectionMatrix     = ShaderProgram::getUniformLocation("projectionMatrix");
        loc_lightCount           = ShaderProgram::getUniformLocation("lightCount");
        for(int i = 0; i < MAX_LIGHTS_ENTITY_SHADER; i++){
            loc_lightPosition[i] = ShaderProgram::getUniformLocation("lights[" + std::to_string(i) + "].position");
            loc_lightColor   [i] = ShaderProgram::getUniformLocation("lights[" + std::to_string(i) + "].color");
            loc_lightFactors [i] = ShaderProgram::getUniformLocation("lights[" + std::to_string(i) + "].factors");
        }

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
    void loadLightCount(int count){
        loadInt(loc_lightCount, count);
    }
    void loadLight(int index, Vector<3>& position, Vector<3>& color, Vector<3>& factors){
        loadVector(loc_lightPosition[index], position);
        loadVector(loc_lightColor   [index], color);
        loadVector(loc_lightFactors [index], factors);
    }
};

#endif    // ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSHADER_H_
