//
// Created by Luecx on 24.06.2021.
//
#include "EntityShader.h"

#include "../../core/glerror.h"

#include <filesystem>
EntityShader::EntityShader()
    : ShaderProgram((std::filesystem::path(__FILE__).parent_path() / "vs.glsl").string(),
                    (std::filesystem::path(__FILE__).parent_path() / "fs.glsl").string()) {}
void EntityShader::getAllUniformLocations() {
    loc_transformationMatrix = ShaderProgram::getUniformLocation("transformationMatrix");
    loc_viewMatrix           = ShaderProgram::getUniformLocation("viewMatrix");
    loc_projectionMatrix     = ShaderProgram::getUniformLocation("projectionMatrix");
    loc_shadowViewMatrix     = ShaderProgram::getUniformLocation("shadowViewMatrix");
    loc_cameraPosition       = ShaderProgram::getUniformLocation("cameraPosition");
    loc_lightCount           = ShaderProgram::getUniformLocation("lightCount");
    for (int i = 0; i < MAX_LIGHTS; i++) {
        loc_lightPosition[i] =
            ShaderProgram::getUniformLocation("lights[" + std::to_string(i) + "].position");
        loc_lightColor[i] =
            ShaderProgram::getUniformLocation("lights[" + std::to_string(i) + "].color");
        loc_lightFactors[i] =
            ShaderProgram::getUniformLocation("lights[" + std::to_string(i) + "].factors");
    }
    loc_shininess    = ShaderProgram::getUniformLocation("shininess");
    loc_useNormalMap = ShaderProgram::getUniformLocation("useNormalMap");
    loc_useSpecularMap       = ShaderProgram::getUniformLocation("useSpecularMap");
    loc_useShadowMap   = ShaderProgram::getUniformLocation("useShadowMap");
    loc_parallaxDepth  = ShaderProgram::getUniformLocation("parallaxDepth");
    loc_textureStretch = ShaderProgram::getUniformLocation("textureStretch");

    loc_colorMap       = ShaderProgram::getUniformLocation("colorMap");
    loc_normalMap      = ShaderProgram::getUniformLocation("normalMap");
    loc_parallaxMap    = ShaderProgram::getUniformLocation("parallaxMap");
    loc_specularMap    = ShaderProgram::getUniformLocation("specularMap");
    loc_shadowMap      = ShaderProgram::getUniformLocation("shadowMap");
}
void EntityShader::bindAttributes() {
    ShaderProgram::bindAttributes();
}
void EntityShader::connectAllTextureUnits() {
    ShaderProgram::connectAllTextureUnits();
    GL_ERROR_CHECK();
    loadInt(loc_colorMap, 0);
    GL_ERROR_CHECK();
    loadInt(loc_normalMap, 1);
    GL_ERROR_CHECK();
//    loadInt(loc_specularMap, 2);
//    GL_ERROR_CHECK();
    loadInt(loc_parallaxMap, 3);
    GL_ERROR_CHECK();
    loadInt(loc_shadowMap, 4);
    GL_ERROR_CHECK();
}
void EntityShader::loadTransformationMatrix(Matrix<4, 4>& transformationMatrix) {
    loadMatrix(loc_transformationMatrix, transformationMatrix);
}
void EntityShader::loadVPMatrix(Matrix<4, 4>& viewMatrix, Matrix<4, 4>& projectionMatrix) {
    loadMatrix(loc_viewMatrix, viewMatrix);
    loadMatrix(loc_projectionMatrix, projectionMatrix);
}
void EntityShader::loadShadowView(bool useShadows, Matrix<4, 4>& viewMatrix) {
    loadBool(loc_useShadowMap, useShadows);
    loadMatrix(loc_shadowViewMatrix, viewMatrix);
}
void EntityShader::loadCameraPosition(Vector<3>& position) {
    loadVector(loc_cameraPosition, position);
}
void EntityShader::loadLightCount(int count) {
    loadInt(loc_lightCount, count);
}
void EntityShader::loadLight(int index, Vector<3>& position, Vector<3>& color, Vector<3>& factors) {
    loadVector(loc_lightPosition[index], position);
    loadVector(loc_lightColor[index], color);
    loadVector(loc_lightFactors[index], factors);
}
void EntityShader::loadMaterialMapUsage(bool useNormalMap, bool useSpecularMap) {
    loadBool(loc_useNormalMap, useNormalMap);
    loadBool(loc_useSpecularMap, useSpecularMap);
}
void EntityShader::loadParallaxDepth(float parallaxDepth) {
    loadFloat(loc_parallaxDepth, parallaxDepth);
}
void EntityShader::loadMaterialData(float shininess) {
    loadFloat(loc_shininess, shininess);
}
void EntityShader::loadTextureStretch(float textureStretch) {
    loadFloat(loc_textureStretch, textureStretch);
}
