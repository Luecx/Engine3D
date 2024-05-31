//
// Created by finn on 5/22/24.
//

#include "TextureID.h"

#include "../core/glerror.h"

void TextureID::bind() {
    glBindTexture(GL_TEXTURE_2D, data_id);
    GL_ERROR_CHECK();
}
void TextureID::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
    GL_ERROR_CHECK();
}
TextureID::TextureID() {
    glGenTextures(1, &data_id);
    GL_ERROR_CHECK();
}
TextureID::~TextureID() {
    if (data_id != 0)
        glDeleteTextures(1, &data_id);
    GL_ERROR_CHECK();
}
