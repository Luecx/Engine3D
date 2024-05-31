//
// Created by Luecx on 31.05.2021.
//

#include "RawModel.h"

#include "../loader/OBJLoader.h"

bool RawModel::load() {
    if (vaoID == nullptr) {
        loaded = loadOBJ(*this, path, true);
    }
    return loaded;
}

void RawModel::unload() {
    vaoID = nullptr;
    vertexCount = 0;
    loaded = false;
}

RawModel::RawModel(const std::string& path)
    : Resource(path) {}
