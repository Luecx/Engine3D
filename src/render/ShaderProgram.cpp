//
// Created by Luecx on 01.06.2021.
//

#include "ShaderProgram.h"

#include "../core/glerror.h"

#include <utility>
ShaderProgram::ShaderProgram(std::string vertex_file, std::string fragment_file)
    : vertexFile(std::move(vertex_file))
    , fragmentFile(std::move(fragment_file)) {}
ShaderProgram::ShaderProgram(std::string vertex_file,
                             std::string fragment_file,
                             std::string geometry_file)
    : vertexFile(std::move(vertex_file))
    , fragmentFile(std::move(fragment_file))
    , geometryFile(std::move(geometry_file)) {}
ShaderProgram::ShaderProgram(std::string vertex_file,
                             std::string fragment_file,
                             std::string tesselation_control_file,
                             std::string tesselation_evaluation_file)
    : vertexFile(std::move(vertex_file))
    , fragmentFile(std::move(fragment_file))
    , tesselationControlFile(std::move(tesselation_control_file))
    , tesselationEvaluationFile(std::move(tesselation_evaluation_file)) {}

void ShaderProgram::destroy() {
    if (!created)
        return;

    GL_ERROR_CHECK();
    stop();
    if (vertexShaderID)
        glDetachShader(programID, vertexShaderID);
    if (fragmentShaderID)
        glDetachShader(programID, fragmentShaderID);
    if (geometryShaderID)
        glDetachShader(programID, geometryShaderID);
    if (tesselationControlShaderID)
        glDetachShader(programID, tesselationControlShaderID);
    if (tesselationEvaluationShaderID)
        glDetachShader(programID, tesselationEvaluationShaderID);
    GL_ERROR_CHECK();

    if (vertexShaderID)
        glDeleteShader(vertexShaderID);
    if (fragmentShaderID)
        glDeleteShader(fragmentShaderID);
    if (geometryShaderID)
        glDeleteShader(geometryShaderID);
    if (tesselationControlShaderID)
        glDeleteShader(tesselationControlShaderID);
    if (tesselationEvaluationShaderID)
        glDeleteShader(tesselationEvaluationShaderID);
    GL_ERROR_CHECK();

    glDeleteProgram(programID);
    GL_ERROR_CHECK();

    created = false;
}

bool ShaderProgram::isCreated() {
    return created;
}

void ShaderProgram::createShader() {
    if (created)
        return;
    created                       = true;

    // load the shaders
    vertexShaderID                = loadShader(vertexFile, GL_VERTEX_SHADER);
    fragmentShaderID              = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
    geometryShaderID              = geometryFile.empty()                ? 0 : loadShader(geometryFile, GL_GEOMETRY_SHADER);
    tesselationControlShaderID    = tesselationControlFile.empty()      ? 0 : loadShader(tesselationControlFile, GL_TESS_CONTROL_SHADER);
    tesselationEvaluationShaderID = tesselationEvaluationFile.empty()   ? 0 : loadShader(tesselationEvaluationFile, GL_TESS_EVALUATION_SHADER);
    GL_ERROR_CHECK();

    // create the program
    programID                     = glCreateProgram();
    GL_ERROR_CHECK();

    // attach the shaders
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    if (geometryShaderID != 0)              glAttachShader(programID, geometryShaderID);
    if (tesselationControlShaderID != 0)    glAttachShader(programID, tesselationControlShaderID);
    if (tesselationEvaluationShaderID != 0) glAttachShader(programID, tesselationEvaluationShaderID);
    GL_ERROR_CHECK();

    // bind the attributes
    bindAttributes();
    GL_ERROR_CHECK();

    // link the program
    glLinkProgram(programID);
    GL_ERROR_CHECK();
    glValidateProgram(programID);
    GL_ERROR_CHECK();

    checkProgramLinking();

    GL_ERROR_CHECK();
    this->start();
    GL_ERROR_CHECK();

    getAllUniformLocations();
    connectAllTextureUnits();
    GL_ERROR_CHECK();

    this->stop();
    GL_ERROR_CHECK();

    checkUnusedUniforms();
    GL_ERROR_CHECK();
}

int ShaderProgram::loadShader(std::string& file, int type) {
    std::ifstream shaderFile(file);
    if (!shaderFile.is_open()) {
        printf("%-13s %-100s %-20s\n", "Compile", ("<" + file + ">").c_str(), "Status = FILE NOT FOUND");
        fflush(stdout);
        exit(0);
        return 0;
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();

    std::string shaderSource = shaderStream.str();
    const char* shaderSourceCStr = shaderSource.c_str();
    GLuint shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &shaderSourceCStr, nullptr);
    glCompileShader(shaderID);

    GL_ERROR_CHECK();
    checkShaderCompilation(file, shaderID);
    GL_ERROR_CHECK();
    return shaderID;
}

int ShaderProgram::getUniformLocation(const std::string& uniformName) {
    GL_ERROR_CHECK();

    int location = glGetUniformLocation(programID, uniformName.c_str());
    // check for errors
    GL_ERROR_CHECK();

    // store a zero inside the usage map if it doesnt exist yet
    auto it = uniformUsageMap.find(uniformName);
    if (it == uniformUsageMap.end()) {
        uniformUsageMap[uniformName] = 0;
    }

    // increment the usage counter if the location is not -1
    if (location != -1) {
        uniformUsageMap[uniformName]++;
    }
    GL_ERROR_CHECK();

    return location;
}

void ShaderProgram::checkUnusedUniforms() {
    for (const auto& pair : uniformUsageMap) {
        if (pair.second == 0) {
            printf("%-13s %-30s %-20s\n",
                   "Warning",
                   pair.first.c_str(),
                   " is unused or cannot be found inside the shader!");
            fflush(stdout);
            warnings = true;
        }
    }
    GL_ERROR_CHECK();
}


void ShaderProgram::checkShaderCompilation(const std::string& file, unsigned int shaderID) {
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
        GL_ERROR_CHECK();
        delete[] infoLog;
        exit(0);
    } else {
        printf("%-13s %-100s %-20s\n", "Compile", ("<" + file + ">").c_str(), "Status = SUCCESSFUL");
        fflush(stdout);
    }
    GL_ERROR_CHECK();
}

void ShaderProgram::checkProgramLinking() {
    GLint linkResult;
    glGetProgramiv(programID, GL_LINK_STATUS, &linkResult);
    if (linkResult == GL_FALSE) {
        printf("%-13s %-100s %-20s\n",
               "Linking",
               "",
               "Status = INCOMPLETE");

        GLint logLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);

        if (logLength > 0) {
            char* infoLog = new char[logLength];
            glGetProgramInfoLog(programID, logLength, NULL, infoLog);
            std::cerr << infoLog << std::endl;
            delete[] infoLog;
        } else {
            std::cerr << "No additional error information available." << std::endl;
        }

        GL_ERROR_CHECK();
        exit(0);
    } else {
        printf("%-13s %-100s %-20s\n",
               "Linking",
               "",
               "Status = SUCCESSFUL");
        fflush(stdout);
    }
    GL_ERROR_CHECK();
}


void ShaderProgram::loadFloat(int location, float value) {
    glUniform1f(location, value);
    // check for errors
    GL_ERROR_CHECK();
}
void ShaderProgram::loadInt(int location, int value) {
    glUniform1i(location, value);
    // check for errors
    GL_ERROR_CHECK();
}
void ShaderProgram::loadVector(int location, Vector<3>& vec) {
    glUniform3f(location, vec[0], vec[1], vec[2]);
    // check for errors
    GL_ERROR_CHECK();
}
void ShaderProgram::loadVector(int location, float x, float y, float z) {
    glUniform3f(location, x, y, z);
    // check for errors
    GL_ERROR_CHECK();
}
void ShaderProgram::loadVector(int location, float x, float y, float z, float w) {
    glUniform4f(location, x, y, z, w);
    // check for errors
    GL_ERROR_CHECK();
}
void ShaderProgram::loadVector(int location, Vector<4>& vec) {
    glUniform4f(location, vec[0], vec[1], vec[2], vec[3]);
    // check for errors
    GL_ERROR_CHECK();
}
void ShaderProgram::loadVector(int location, Vector<2>& vec) {
    glUniform2f(location, vec[0], vec[1]);
    // check for errors
    GL_ERROR_CHECK();
}
void ShaderProgram::loadBool(int location, bool value) {
    float toLoad = 0;
    if (value) {
        toLoad = 1;
    }
    glUniform1f(location, toLoad);
    GL_ERROR_CHECK();
}
void ShaderProgram::loadMatrix(int location, Matrix<4, 4>& matrix) {
    float values[16] {};
    for (int i = 0; i < 16; i++) {
        values[i] = matrix[i];
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, values);
    GL_ERROR_CHECK();
}
void ShaderProgram::start() {
    if (!created)
        return;
    glUseProgram(programID);
    GL_ERROR_CHECK();
}
void ShaderProgram::stop() {
    glUseProgram(0);
    GL_ERROR_CHECK();
}
