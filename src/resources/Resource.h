//
// Created by finn on 5/23/24.
//

#ifndef ENGINE3D_RESOURCE_H
#define ENGINE3D_RESOURCE_H

#include <string>

class Resource {

    public:
    const std::string path = "";

    Resource(const std::string& path);

    bool loaded = false;

    virtual bool load() = 0;
    virtual void unload() = 0;

};

#endif    // ENGINE3D_RESOURCE_H
