//
// Created by Luecx on 03.06.2021.
//

#ifndef ENGINE3D_SRC_ENTITIES_TEXTUREDMODEL_H_
#define ENGINE3D_SRC_ENTITIES_TEXTUREDMODEL_H_

#include "../material/EntityMaterial.h"
#include "../model/RawModel.h"
class TexturedModel {

    public:
    RawModel        rawModel;
    EntityMaterial  material;


};

#endif    // ENGINE3D_SRC_ENTITIES_TEXTUREDMODEL_H_
