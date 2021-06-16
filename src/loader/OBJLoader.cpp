//
// Created by Luecx on 01.06.2021.
//

#include "OBJLoader.h"

#include "../math/Vector.h"
#include "../model/RawModel.h"
#include "VAOLoader.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Vertex {
    Vector<3>              position;
    int                    index;
    int                    textureIndex    = -1;
    int                    normalIndex     = -1;
    std::vector<Vector<3>> tangents {};
    Vector<3>              averagedTangent;
};



Vertex& processAlreadyProcessedVertex(Vertex& previousVertex, int newTextureIndex, int newNormalIndex, std::vector<int>& indices,
                                     std::vector<Vertex>& vertices) {

    if (previousVertex.textureIndex == newTextureIndex && previousVertex.normalIndex == newNormalIndex) {
        indices.push_back(previousVertex.index);
        return previousVertex;
    } else {
        Vertex duplicateVertex {previousVertex.position, static_cast<int>(vertices.size())};
        duplicateVertex.textureIndex = newTextureIndex;
        duplicateVertex.normalIndex  = newNormalIndex;
        duplicateVertex.index        = vertices.size();
        vertices.emplace_back(duplicateVertex);
        indices.push_back(duplicateVertex.index);
        return vertices[vertices.size()-1];
    }
}


Vertex& processVertex(std::string& vertex, std::vector<Vertex>& vertices, std::vector<int>& indices) {
    // get the three separated values
    std::stringstream ss(vertex);
    std::string       k1, k2, k3;
    getline(ss, k1, '/');
    getline(ss, k2, '/');
    getline(ss, k3, '/');

    int index        = std::stoi(k1) - 1;
    int textureIndex = std::stoi(k2) - 1;
    int normalIndex  = std::stoi(k3) - 1;

    if (vertices[index].textureIndex == -1 || vertices[index].normalIndex == -1) {
        vertices[index].textureIndex = textureIndex;
        vertices[index].normalIndex  = normalIndex;
        indices.push_back(index);
        return vertices[index];
    } else {
        return processAlreadyProcessedVertex(vertices[index], textureIndex, normalIndex, indices, vertices);
    }
}

void calculateTangents(Vertex &v1, Vertex& v2, Vertex& v3, std::vector<Vector<2>> textureCoords){
    Vector<3> deltaPos2 = v2.position - v1.position;
    Vector<3> deltaPos3 = v3.position - v1.position;
    Vector<2> uv1 = textureCoords[v1.textureIndex];
    Vector<2> uv2 = textureCoords[v2.textureIndex];
    Vector<2> uv3 = textureCoords[v3.textureIndex];
    Vector<2> deltaUv2 = uv2-uv1;
    Vector<2> deltaUv3 = uv3-uv1;

    float r = 1.0 / (deltaUv2[0] * deltaUv3[1] - deltaPos2[1] * deltaUv3[0]);
    deltaPos2 *= deltaUv3[2];
    deltaPos3 *= deltaUv2[2];
    Vector<3> tangent = deltaPos2 - deltaPos3;
    tangent *= r;
    v1.tangents.push_back(tangent);
    v2.tangents.push_back(tangent);
    v3.tangents.push_back(tangent);
}

void removeUnusedVertices(std::vector<Vertex>& vertices){
    for(Vertex &v:vertices){

        // average tangents
        if(v.tangents.size() > 0){
            Vector<3> sum{};
            for(Vector<3> &t:v.tangents){
                sum += t;
            }
            sum *= 1.0 / v.tangents.size();
            v.averagedTangent = sum;
        }

        if(v.textureIndex == -1 || v.normalIndex == -1){
            v.textureIndex = -1;
            v.normalIndex = -1;
        }

    }
}

RawModel loadOBJ(const std::string& objFileName, bool computeTangents) {
    std::ifstream          ifs(objFileName);

    std::string            line;

    std::vector<Vertex>    vertices {};
    std::vector<Vector<2>> textureCoords {};
    std::vector<Vector<3>> normals {};
    std::vector<int>       indices {};

    int faceCount  = 0;
    std::stringstream      ss {};
    // going through each line
    while (std::getline(ifs, line)) {

        if (line.rfind("#", 0) == 0)
            continue;
        ss.clear();
        std::string key;
        std::string v1, v2, v3;

        ss << line;
        ss >> key >> v1 >> v2 >> v3;

        if (key == "v") {
            Vector<3> position {std::stod(v1), std::stod(v2), std::stod(v3)};
            Vertex    vertex {position, static_cast<int>(vertices.size())};
            vertices.push_back(vertex);
        } else if (key == "vt") {
            Vector<2> textureCoord {std::stod(v1), std::stod(v2)};
            textureCoords.push_back(textureCoord);
        } else if (key == "vn") {
            Vector<3> normal {std::stod(v1), std::stod(v2), std::stod(v3)};
            normals.push_back(normal);
        } else if (key == "f") {
            faceCount ++;
            Vertex ve1 = processVertex(v1, vertices, indices);
            Vertex ve2 = processVertex(v2, vertices, indices);
            Vertex ve3 = processVertex(v3, vertices, indices);
            if(computeTangents){
                calculateTangents(ve1, ve2, ve3, textureCoords);
            }
        }
    }
    ifs.close();
    removeUnusedVertices(vertices);

    std::vector<float> finalVertices{};
    std::vector<float> finalTextureCoords{};
    std::vector<float> finalNormals{};
    std::vector<float> finalTangents{};

    for(Vertex &v:vertices){
        finalVertices.push_back(v.position[0]);
        finalVertices.push_back(v.position[1]);
        finalVertices.push_back(v.position[2]);

        finalTextureCoords.push_back(textureCoords[v.textureIndex][0]);
        finalTextureCoords.push_back(textureCoords[v.textureIndex][1]);

        finalNormals.push_back(normals[v.normalIndex][0]);
        finalNormals.push_back(normals[v.normalIndex][1]);
        finalNormals.push_back(normals[v.normalIndex][2]);

        finalTangents.push_back(v.averagedTangent[0]);
        finalTangents.push_back(v.averagedTangent[1]);
        finalTangents.push_back(v.averagedTangent[2]);
    }


    if(computeTangents){

        return loadToVao(finalVertices, finalTextureCoords, finalNormals, finalTangents, indices);
    }else{
        return loadToVao(finalVertices, finalTextureCoords, finalNormals, indices);

    }
}