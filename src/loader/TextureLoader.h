//
// Created by Luecx on 01.06.2021.
//

#ifndef ENGINE3D_SRC_LOADER_TEXTURELOADER_H_
#define ENGINE3D_SRC_LOADER_TEXTURELOADER_H_

#include "../material/Texture.h"

#define GLFW_INCLUDE_NONE
#include "../glad.h"

#include <string>
Texture loadTexture(const std::string& file);
#endif    // ENGINE3D_SRC_LOADER_TEXTURELOADER_H_
