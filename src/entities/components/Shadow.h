//
// Created by Luecx on 04.06.2021.
//

#ifndef ENGINE3D_SRC_ENTITIES_COMPONENTS_SHADOW_H_
#define ENGINE3D_SRC_ENTITIES_COMPONENTS_SHADOW_H_

namespace ecs {

struct Shadow : public Component {
    bool castsShadow    = true;
    bool receivesShadow = true;
}

}    // namespace ecs

#endif    // ENGINE3D_SRC_ENTITIES_COMPONENTS_SHADOW_H_
