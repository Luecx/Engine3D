//
// Created by finn on 5/22/24.
//

#ifndef ENGINE3D_GLERROR_H
#define ENGINE3D_GLERROR_H

#include "../glad.h"
#include <iostream>
#include <string>

// Function to translate GL error codes to readable messages
inline std::string getGLErrorString(GLenum error) {
    switch (error) {
        case GL_NO_ERROR:
            return "No error";
        case GL_INVALID_ENUM:
            return "Invalid enum";
        case GL_INVALID_VALUE:
            return "Invalid value";
        case GL_INVALID_OPERATION:
            return "Invalid operation";
        case GL_STACK_OVERFLOW:
            return "Stack overflow";
        case GL_STACK_UNDERFLOW:
            return "Stack underflow";
        case GL_OUT_OF_MEMORY:
            return "Out of memory";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "Invalid framebuffer operation";
        default:
            return "Unknown error";
    }
}

// Function to check and print OpenGL errors
inline void glErrorCheck(const char* function, const char* file, int line) {
    GLenum error = glGetError();
    while (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error in function '" << function
                  << "' at " << file << ":" << line << " - "
                  << getGLErrorString(error) << " (" << error << ")" << std::endl;
        error = glGetError(); // Check for additional errors
        exit(0);
    }
}

// Macro to wrap around OpenGL function calls for easier debugging
#define GL_ERROR_CHECK() glErrorCheck(__FUNCTION__, __FILE__, __LINE__)

#endif    // ENGINE3D_GLERROR_H
