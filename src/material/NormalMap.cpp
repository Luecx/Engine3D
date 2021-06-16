//
// Created by Luecx on 16.06.2021.
//
#include "NormalMap.h"
NormalMap::NormalMap() {
}
NormalMap::NormalMap(GLuint texture_id, int width, int height) : Texture(texture_id, width, height) {
}
NormalMap::NormalMap(Texture&& other) : Texture(other) {
}
NormalMap::NormalMap(const Texture& other) : Texture(other) {
}
