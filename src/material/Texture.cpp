//
// Created by Luecx on 01.06.2021.
//

#include "Texture.h"

#include "../loader/TextureLoader.h"

#include <iostream>

Texture::Texture() {
    cleanTexture = false;
}

Texture::Texture(GLuint texture_id,  int width, int height)
    : textureID(texture_id), width(width), height(height) {
    cleanTexture = true;
}
Texture::Texture(Texture&& other) {
    textureID          = other.textureID;
    cleanTexture       = other.cleanTexture;
    width              = other.width;
    height             = other.height;

    other.cleanTexture = false;
}
Texture::Texture(const Texture& other) {
    textureID    = other.textureID;
    cleanTexture = false;
    width        = other.width;
    height       = other.height;
}

Texture& Texture::operator=(Texture&& other) {
    clean();

    textureID          = other.textureID;
    cleanTexture       = other.cleanTexture;
    width              = other.width;
    height             = other.height;

    other.cleanTexture = false;
    return *this;
}
Texture& Texture::operator=(const Texture& other) {
    clean();

    textureID    = other.textureID;
    cleanTexture = false;
    width        = other.width;
    height       = other.height;

    return *this;
}
Texture::~Texture() {
    clean();
}

void Texture::clean(){
    if (cleanTexture) {
        std::cout << "glDeleteTextures " << textureID << std::endl;
        glDeleteTextures(1, &textureID);
    }
}

GLuint Texture::getTextureId() const {
    return textureID;
}
int Texture::getWidth() const {
    return width;
}
int Texture::getHeight() const {
    return height;
}
