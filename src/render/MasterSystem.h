//
// Created by Luecx on 06.06.2021.
//

#ifndef ENGINE3D_SRC_RENDER_MASTERSYSTEM_H_
#define ENGINE3D_SRC_RENDER_MASTERSYSTEM_H_

#include "../light/LightSource.h"

#include <vector>
class MasterSystem {

    private:
    std::vector<LightSource> lightSource{};

    template<typename type>
    int add(std::vector<type> &vector){
        vector.push_back(type{});
        return vector.size();
    }

    int remove(){

    }
};

#endif    // ENGINE3D_SRC_RENDER_MASTERSYSTEM_H_
