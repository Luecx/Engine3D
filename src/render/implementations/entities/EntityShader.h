//
// Created by Luecx on 02.06.2021.
//

#ifndef ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSHADER_H_
#define ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSHADER_H_

#include "../../../material/NormalMap.h"
#include "../../ShaderProgram.h"

#define MAX_LIGHTS_ENTITY_SHADER 4

class EntityShader : public ShaderProgram {

    private:
    int loc_transformationMatrix;
    int loc_viewMatrix;
    int loc_projectionMatrix;
    int loc_lightCount;
    int loc_lightPosition[MAX_LIGHTS_ENTITY_SHADER];
    int loc_lightColor[MAX_LIGHTS_ENTITY_SHADER];
    int loc_lightFactors[MAX_LIGHTS_ENTITY_SHADER];
    int loc_shineDamper;
    int loc_reflectivity;
    int loc_useNormalMap;
    int loc_useSpecularMap;
    int loc_textureStretch;

    int loc_normalMap;
    int loc_colorMap;
    int loc_specularMap;

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
        loc_shineDamper          = ShaderProgram::getUniformLocation("shineDamper");
        loc_reflectivity         = ShaderProgram::getUniformLocation("reflectivity");
        loc_useNormalMap         = ShaderProgram::getUniformLocation("useNormalMap");
        loc_useSpecularMap       = ShaderProgram::getUniformLocation("useSpecularMap");
        loc_textureStretch       = ShaderProgram::getUniformLocation("textureStretch");

        loc_colorMap             = ShaderProgram::getUniformLocation("colorMap");
        loc_normalMap            = ShaderProgram::getUniformLocation("normalMap");
        loc_specularMap          = ShaderProgram::getUniformLocation("specularMap");
    }
    void bindAttributes() override {
        ShaderProgram::bindAttributes();
    }
    void connectAllTextureUnits() override {
        ShaderProgram::connectAllTextureUnits();
        loadInt(loc_colorMap, 0);
        loadInt(loc_normalMap, 1);
        loadInt(loc_specularMap, 2);
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
    void loadMaterialMapUsage(bool useNormalMap, bool useSpecularMap){
        loadBool(loc_useNormalMap, useNormalMap);
        loadBool(loc_useSpecularMap, useSpecularMap);
    }
    void loadMaterialData(float shineDamper,float reflectivity){
        loadFloat(loc_shineDamper, shineDamper);
        loadFloat(loc_reflectivity, reflectivity);
    }
    void loadTextureStretch(float textureStretch){
        loadFloat(loc_textureStretch, textureStretch);
    }
};

#endif    // ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSHADER_H_
