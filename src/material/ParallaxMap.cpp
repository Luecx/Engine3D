//
// Created by Luecx on 16.06.2021.
//
#include "ParallaxMap.h"

ParallaxMap::ParallaxMap(float depth) : depth(depth) {
}
ParallaxMap::ParallaxMap(GLuint texture_id, int width, int height, float depth) : Texture(texture_id, width, height), depth(depth) {
}
ParallaxMap::ParallaxMap(Texture&& other, float depth) : Texture(other), depth(depth) {
}
ParallaxMap::ParallaxMap(const Texture& other, float depth) : Texture(other), depth(depth) {
}
ParallaxMap::ParallaxMap() {
}
