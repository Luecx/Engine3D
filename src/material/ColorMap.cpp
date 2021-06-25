//
// Created by Luecx on 16.06.2021.
//
#include "ColorMap.h"
ColorMap::ColorMap() {
}
ColorMap::ColorMap(GLuint texture_id, int p_width, int p_height) : Texture(texture_id, p_width, p_height) {
}
ColorMap::ColorMap(Texture&& other) : Texture(other) {
}
ColorMap::ColorMap(const Texture& other) : Texture(other) {
}