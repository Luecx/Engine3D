//
// Created by Luecx on 16.06.2021.
//
#include "SpecularMap.h"
SpecularMap::SpecularMap() {
}
SpecularMap::SpecularMap(GLuint texture_id, int width, int height) : Texture(texture_id, width, height) {
}
SpecularMap::SpecularMap(Texture&& other) : Texture(other) {
}
SpecularMap::SpecularMap(const Texture& other) : Texture(other) {
}
