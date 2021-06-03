//
// Created by Luecx on 01.06.2021.
//

#include "ShaderProgram.h"

#include <utility>
ShaderProgram::ShaderProgram(std::string vertex_file, std::string fragment_file)
    : vertexFile(std::move(vertex_file)), fragmentFile(std::move(fragment_file)) {
}
ShaderProgram::ShaderProgram(std::string vertex_file, std::string fragment_file, std::string geometry_file)
    : vertexFile(std::move(vertex_file)), fragmentFile(std::move(fragment_file)), geometryFile(std::move(geometry_file)) {
}
ShaderProgram::ShaderProgram(std::string vertex_file, std::string fragment_file, std::string tesselation_control_file,
                             std::string tesselation_evaluation_file)
    : vertexFile(std::move(vertex_file)), fragmentFile(std::move(fragment_file)),
      tesselationControlFile(std::move(tesselation_control_file)), tesselationEvaluationFile(std::move(tesselation_evaluation_file)) {
}

ShaderProgram::~ShaderProgram() {

    if (!created)
        return;

    stop();
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDetachShader(programID, geometryShaderID);
    glDetachShader(programID, tesselationControlShaderID);
    glDetachShader(programID, tesselationEvaluationShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    glDeleteShader(geometryShaderID);
    glDeleteShader(tesselationControlShaderID);
    glDeleteShader(tesselationEvaluationShaderID);

    glDeleteProgram(programID);
}

bool ShaderProgram::isCreated() {
    return created;
}

void ShaderProgram::createShader() {
    if (created)
        return;
    created                       = true;

    vertexShaderID                = loadShader(vertexFile, GL_VERTEX_SHADER);
    fragmentShaderID              = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
    geometryShaderID              = geometryFile.empty() ? 0 : loadShader(geometryFile, GL_GEOMETRY_SHADER);
    tesselationControlShaderID    = tesselationControlFile.empty() ? 0 : loadShader(tesselationControlFile, GL_GEOMETRY_SHADER);
    tesselationEvaluationShaderID = tesselationEvaluationFile.empty() ? 0 : loadShader(tesselationEvaluationFile, GL_GEOMETRY_SHADER);
    programID                     = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    if (geometryShaderID != 0) {
        glAttachShader(programID, geometryShaderID);
    }
    if (tesselationControlShaderID != 0) {
        glAttachShader(programID, tesselationControlShaderID);
    }
    if (tesselationEvaluationShaderID != 0) {
        glAttachShader(programID, tesselationEvaluationShaderID);
    }
    bindAttributes();
    glLinkProgram(programID);
    glValidateProgram(programID);
    getAllUniformLocations();
    this->start();
    connectAllTextureUnits();
    this->stop();
    printf("%-13s %-100s %-20s\n", "Linking", "", warnings ? "Status = WARNINGS":"Status = SUCCESSFUL");
    fflush(stdout);
}
int ShaderProgram::loadShader(std::string& file, int type) {

    std::string shaderSource;
    try {
        std::getline(std::ifstream(file), shaderSource, '\0');
    } catch (...) {
        printf("%-13s %-100s %-20s%n", "Compile", ("<" + file + ">").c_str(), "Status = NOT EXISTING SOURCE");
        fflush(stdout);
        return 0;
    }
    auto dataPtr  = shaderSource.c_str();
    auto shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &dataPtr, 0);
    glCompileShader(shaderID);

    GLint compilationResult;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationResult);

    if (compilationResult == GL_FALSE) {
        printf("%-13s %-100s %-20s\n", "Compile", ("<" + file + ">").c_str(), "Status = INCOMPLETE");
        fflush(stdout);
        GLint logLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
        auto* infoLog = new char[logLength + 1];
        glGetShaderInfoLog(shaderID, logLength, NULL, infoLog);
        std::cerr << infoLog << std::endl;
        delete[] infoLog;
        return 0;
    } else {
        printf("%-13s %-100s %-20s\n", "Compile", ("<" + file + ">").c_str(), "Status = SUCCESSFUL");
        fflush(stdout);
        return shaderID;
    }
}

int ShaderProgram::getUniformLocation(const std::string& uniformName) {
    int location = glGetUniformLocation(programID, uniformName.c_str());
    if(location == -1){
        printf("%-13s %-30s %-20s\n", "Warning", uniformName.c_str(), " is unused or cannot be found inside the shader!");
        fflush(stdout);
        warnings = true;
    }
    return location;
}

void ShaderProgram::loadFloat(int location, float value) {
    glUniform1f(location, value);
}
void ShaderProgram::loadInt(int location, int value) {
    glUniform1i(location, value);
}
void ShaderProgram::loadVector(int location, Vector<3>& vec) {
    glUniform3f(location, vec[0], vec[1], vec[2]);
}
void ShaderProgram::loadVector(int location, float x, float y, float z) {
    glUniform3f(location, x, y, z);
}
void ShaderProgram::loadVector(int location, float x, float y, float z, float w) {
    glUniform4f(location, x, y, z, w);
}
void ShaderProgram::loadVector(int location, Vector<4>& vec) {
    glUniform4f(location, vec[0], vec[1], vec[2], vec[3]);
}
void ShaderProgram::loadVector(int location, Vector<2>& vec) {
    glUniform2f(location, vec[0], vec[1]);
}
void ShaderProgram::loadBool(int location, bool value) {
    float toLoad = 0;
    if (value) {
        toLoad = 1;
    }

    glUniform1f(location, toLoad);
}
void ShaderProgram::loadMatrix(int location, Matrix<4, 4>& matrix) {
    float values[16] {};
    for (int i = 0; i < 16; i++) {
        values[i] = matrix[i];
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, values);
}
void ShaderProgram::start() {
    if (!created)
        return;
    glUseProgram(programID);
}
void ShaderProgram::stop() {
    if (!created)
        return;
    glUseProgram(0);
}
