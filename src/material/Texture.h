//
// Created by Luecx on 01.06.2021.
//

#ifndef ENGINE3D_SRC_MODEL_TEXTURE_H_
#define ENGINE3D_SRC_MODEL_TEXTURE_H_

#define GLFW_INCLUDE_NONE
#include "../glad.h"

#include <GLFW/glfw3.h>
#include <string>

class Texture {

    private:
    GLuint   textureID;
    bool     cleanTexture = false;

    int      width;
    int      height;

    public:
    Texture();
    Texture(GLuint texture_id, int width, int height);
    Texture(Texture&& other);
    Texture(const Texture& other);
    Texture& operator=(Texture&& other);
    Texture& operator=(const Texture& other);

    virtual ~Texture();

    GLuint getTextureId() const;
    int    getWidth() const;
    int    getHeight() const;
};

#endif    // ENGINE3D_SRC_MODEL_TEXTURE_H_
