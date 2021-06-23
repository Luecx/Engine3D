//
// Created by Luecx on 01.06.2021.
//

#ifndef ENGINE3D_SRC_LOADER_OBJLOADER_H_
#define ENGINE3D_SRC_LOADER_OBJLOADER_H_

#include "../model/RawModel.h"
#include <string>

RawModel loadOBJ(const std::string& objFileName, bool computeTangents=true);

#endif    // ENGINE3D_SRC_LOADER_OBJLOADER_H_
