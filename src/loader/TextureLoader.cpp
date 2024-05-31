//
// Created by Luecx on 01.06.2021.
//
#include "TextureLoader.h"

#include "../core/glerror.h"

#include <algorithm>
#include <fstream>
#include <iostream>

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t fileType;      // File type, should be BM for bitmap files
    uint32_t fileSize;      // Size of the file in bytes
    uint16_t reserved1;     // Reserved, should be 0
    uint16_t reserved2;     // Reserved, should be 0
    uint32_t offsetData;    // Offset from beginning of file to the beginning of the bitmap data
};

struct BMPInfoHeader {
    uint32_t size;               // Size of this header
    int32_t  width;              // Width of the bitmap in pixels
    int32_t  height;             // Height of the bitmap in pixels
    uint16_t planes;             // Number of color planes, must be 1
    uint16_t bitCount;           // Number of bits per pixel
    uint32_t compression;        // Compression method being used
    uint32_t sizeImage;          // Size of the raw bitmap data
    int32_t  xPixelsPerMeter;    // Horizontal resolution
    int32_t  yPixelsPerMeter;    // Vertical resolution
    uint32_t colorsUsed;         // Number of colors in the color palette
    uint32_t colorsImportant;    // Number of important colors
};
#pragma pack(pop)

uint8_t* loadBitmap(const char* filepath, int& width, int& height) {
    BMPHeader     header;
    BMPInfoHeader infoHeader;

    std::ifstream file(filepath, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Could not open file " << filepath << std::endl;
        return nullptr;
    }

    // Read the BMP header
    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    if (header.fileType != 0x4D42) {    // 'BM' in hexadecimal
        std::cerr << "Not a valid BMP file" << std::endl;
        return nullptr;
    }

    // Read the BMP info header
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    // Move the file cursor to the start of the bitmap data
    file.seekg(header.offsetData, std::ios::beg);

    // Allocate memory for the bitmap data
    uint8_t* data = new uint8_t[infoHeader.sizeImage];

    // Read the bitmap data
    file.read(reinterpret_cast<char*>(data), infoHeader.sizeImage);

    // Close the file
    file.close();

    width  = infoHeader.width;
    height = infoHeader.height;

    // show all data in both headers
    std::cout << "File type: " << header.fileType << std::endl;
    std::cout << "File size: " << header.fileSize << std::endl;
    std::cout << "Reserved 1: " << header.reserved1 << std::endl;
    std::cout << "Reserved 2: " << header.reserved2 << std::endl;
    std::cout << "Offset data: " << header.offsetData << std::endl;
    std::cout << "Size: " << infoHeader.size << std::endl;
    std::cout << "Width: " << infoHeader.width << std::endl;
    std::cout << "Height: " << infoHeader.height << std::endl;
    std::cout << "Planes: " << infoHeader.planes << std::endl;
    std::cout << "Bit count: " << infoHeader.bitCount << std::endl;
    std::cout << "Compression: " << infoHeader.compression << std::endl;
    std::cout << "Size image: " << infoHeader.sizeImage << std::endl;
    std::cout << "X pixels per meter: " << infoHeader.xPixelsPerMeter << std::endl;
    std::cout << "Y pixels per meter: " << infoHeader.yPixelsPerMeter << std::endl;
    std::cout << "Colors used: " << infoHeader.colorsUsed << std::endl;
    std::cout << "Colors important: " << infoHeader.colorsImportant << std::endl;

    return data;
}

std::tuple<TextureIDPtr, int, int> loadTexture(const std::string& file) {
    uint8_t* data;
    int      width;
    int      height;

    // generate the texture
    TextureIDPtr textureIDPtr = std::make_shared<TextureID>();
    GL_ERROR_CHECK();

    textureIDPtr->bind();
    GL_ERROR_CHECK();

    // load the raw data
    if (file.find(".bmp") != std::string::npos) {
        data = loadBitmap(file.c_str(), width, height);
    } else {
        return {nullptr, 0, 0};
    }

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    // generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    delete data;

    GL_ERROR_CHECK();
    return {textureIDPtr, width, height};
}
