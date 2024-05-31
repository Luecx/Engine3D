//
// Created by Luecx on 01.06.2021.
//

#ifndef ENGINE3D_SRC_SHADER_SHADERPROGRAM_H_
#define ENGINE3D_SRC_SHADER_SHADERPROGRAM_H_

#include "../glad.h"
#include "../math/Matrix.h"
#include "../math/Vector.h"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>


class ShaderProgram {

    private:
    bool        created  = false;
    bool        warnings = false;

    std::string vertexFile {};
    std::string fragmentFile {};
    std::string geometryFile {};
    std::string tesselationControlFile {};
    std::string tesselationEvaluationFile {};

    GLuint      programID                     = 0;
    GLuint      vertexShaderID                = 0;
    GLuint      fragmentShaderID              = 0;
    GLuint      geometryShaderID              = 0;
    GLuint      tesselationControlShaderID    = 0;
    GLuint      tesselationEvaluationShaderID = 0;

    std::unordered_map<std::string, int> uniformUsageMap;

    public:
    ShaderProgram(std::string vertex_file, std::string fragment_file);
    ShaderProgram(std::string vertex_file, std::string fragment_file, std::string geometry_file);
    ShaderProgram(std::string vertex_file,
                  std::string fragment_file,
                  std::string tesselation_control_file,
                  std::string tesselation_evaluation_file);


    private:
    int loadShader(std::string& file, int type);
    void checkUnusedUniforms();
    void checkShaderCompilation(const std::string& file, unsigned int shaderID);
    void checkProgramLinking();

    protected:
    virtual void getAllUniformLocations() {};
    virtual void bindAttributes() {};
    virtual void connectAllTextureUnits() {};

    int          getUniformLocation(const std::string& uniformName);

    public:
    void loadFloat(int location, float value);
    void loadInt(int location, int value);
    void loadVector(int location, Vector<3>& vec);
    void loadVector(int location, float x, float y, float z);
    void loadVector(int location, float x, float y, float z, float w);
    void loadVector(int location, Vector<4>& vec);
    void loadVector(int location, Vector<2>& vec);
    void loadBool(int location, bool value);
    void loadMatrix(int location, Matrix<4, 4>& matrix);

    public:
    bool isCreated();
    void createShader();
    void start();
    void stop();
    void destroy();
};

#endif    // ENGINE3D_SRC_SHADER_SHADERPROGRAM_H_
