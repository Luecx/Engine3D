//
// Created by finn on 5/22/24.
//

#ifndef ENGINE3D_GLDATA_H
#define ENGINE3D_GLDATA_H

#include "../glad.h"

class GLData {
    protected:
    GLuint data_id{};

    public:
    // use this as a GLuint
    explicit operator GLuint() const;

    public:
    virtual void bind() {};
    virtual void unbind() {};

};

#endif    // ENGINE3D_GLDATA_H
