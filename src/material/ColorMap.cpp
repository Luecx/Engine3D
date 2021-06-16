//
// Created by Luecx on 16.06.2021.
//
#include "ColorMap.h"
ColorMap::ColorMap() {
}
ColorMap::ColorMap(GLuint texture_id, int width, int height) : Texture(texture_id, width, height) {
}
ColorMap::ColorMap(Texture&& other) : Texture(other) {
}
ColorMap::ColorMap(const Texture& other) : Texture(other) {
}