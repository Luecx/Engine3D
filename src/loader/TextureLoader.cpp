//
// Created by Luecx on 01.06.2021.
//
#include "TextureLoader.h"

#include <algorithm>
#include <iostream>

uint8_t* loadBMP(const std::string& file, int& width, int& height){
    // Data read from the header of the BMP file
    unsigned char header[54];    // Each BMP file begins by a 54-bytes header
    unsigned int  dataPos;       // Position in the file where the actual data begins
    unsigned int  imageSize;    // = width*height*3
    // Actual RGB data
    // Open the file
    FILE*         f = fopen(file.c_str(), "rb");
    if (!f) {
        printf("Image could not be opened\n");
        exit(-1);
    }

    if (fread(header, 1, 54, f) != 54) {    // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        exit(-1);
    }

    if (header[0] != 'B' || header[1] != 'M') {
        printf("Not a correct BMP file\n");
        exit(-1);
    }

    dataPos   = *(int*) &(header[0x0A]);
    imageSize = *(int*) &(header[0x22]);
    width     = *(int*) &(header[0x12]);
    height    = *(int*) &(header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (imageSize == 0)
        imageSize = width * height * 3;    // 3 : one byte for each Red, Green and Blue component
    if (dataPos == 0)
        dataPos = 54;    // The BMP header is done that way

    // Create a buffer
    auto *data = new uint8_t[imageSize]{};

    // Read the actual data from the file into the buffer
    fread(data, sizeof(uint8_t), imageSize, f);

    // Everything is in memory now, the file can be closed
    fclose(f);
    return data;
}

Texture loadTexture(const std::string& file) {
    uint8_t* data;
    int width;
    int height;
    GLuint textureID;

    // load the raw data
    if (file.find(".bmp") != std::string::npos){
        data = loadBMP(file,  width, height);
    }else{
        return {};
    }

    // generate the texture
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    // generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

    delete data;

    // create the texture
    Texture texture{textureID, width, height};
    return texture;
}
