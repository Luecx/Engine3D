//
// Created by Luecx on 24.06.2021.
//

#include "ShadowShader.h"
ShadowShader::ShadowShader()
    : ShaderProgram(
    R"(C:\Users\Luecx\CLionProjects\Engine3D\src\render\shadow\vs.glsl)",
    R"(C:\Users\Luecx\CLionProjects\Engine3D\src\render\shadow\fs.glsl)") {
}
void ShadowShader::getAllUniformLocations() {
    ShaderProgram::getAllUniformLocations();
    loc_transformationMatrix = ShaderProgram::getUniformLocation("transformationMatrix");
    loc_viewMatrix           = ShaderProgram::getUniformLocation("viewMatrix");
    loc_projectionMatrix     = ShaderProgram::getUniformLocation("projectionMatrix");
}
void ShadowShader::bindAttributes() {
    ShaderProgram::bindAttributes();
}
void ShadowShader::connectAllTextureUnits() {
    ShaderProgram::connectAllTextureUnits();
}
void ShadowShader::loadTransformationMatrix(Matrix<4, 4>& transformationMatrix) {
    loadMatrix(loc_transformationMatrix, transformationMatrix);
}
void ShadowShader::loadVPMatrix(Matrix<4, 4>& viewMatrix, Matrix<4, 4>& projectionMatrix) {
    loadMatrix(loc_viewMatrix, viewMatrix);
    loadMatrix(loc_projectionMatrix, projectionMatrix);
}