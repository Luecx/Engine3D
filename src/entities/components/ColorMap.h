//
// Created by Luecx on 04.06.2021.
//

#ifndef ENGINE3D_SRC_ENTITIES_COMPONENTS_COLORMAP_H_
#define ENGINE3D_SRC_ENTITIES_COMPONENTS_COLORMAP_H_

namespace ecs {
struct ColorMap : public Component {
    Texture texture{};
};

}    // namespace ecs

#endif    // ENGINE3D_SRC_ENTITIES_COMPONENTS_COLORMAP_H_
