
#define GLFW_INCLUDE_NONE
#include "camera/OrthogonalCamera.h"
#include "camera/PerspectiveCamera.h"
#include "components/LightSource.h"
//#include "ecs/core.h"
#include "loader/OBJLoader.h"
#include "loader/TextureLoader.h"
#include "material/ColorMap.h"
#include "material/TextureStretch.h"
#include "render/MasterSystem.h"

int main() {

    MasterSystem      master {};

    PerspectiveCamera camera {};

    camera.getPosition()[2] = 1;
//    camera.getPosition()[0] = 1;
    camera.getProjectionMatrix();

    ecs::Entity* cameraEntity = master.ecs.spawn();
    cameraEntity->assign<Camera*>(&camera);
    cameraEntity->assign<SimpleControl>();


    RawModel       model          = loadOBJ(R"(C:\Users\Luecx\CLionProjects\Engine3D\res\models\lucy.obj)", true);
    RawModel       groundModel    = loadOBJ(R"(C:\Users\Luecx\CLionProjects\Engine3D\res\models\ground.obj)", true);
    Texture        texture        = loadTexture(R"(C:\Users\Luecx\CLionProjects\Engine3D\res\colormaps\uv.bmp)");
    Texture        statureTexture = loadTexture(R"(C:\Users\Luecx\CLionProjects\Engine3D\res\colormaps\white.bmp)");
    Texture        normalTexture  = loadTexture(R"(C:\Users\Luecx\CLionProjects\Engine3D\res\normals\rustyMetal.bmp)");

    ecs::Entity*   entity  = master.ecs.spawn();
    ecs::Entity*   entity2 = master.ecs.spawn();
    ecs::Entity*   entity3 = master.ecs.spawn();
//    ecs::Entity*   entity4 = master.ecs.spawn();

    entity->assign<ComplexTransformation>(Vector<3> {}, Vector<3> {0, +20, 0});
    entity->assign<ColorMap>(statureTexture);
    entity->assign<NormalMap>(normalTexture);
    entity->assign<TextureStretch>(10.0f);
    entity->assign<RawModel>(model);
    entity->assign<LightReflection>(1.f, 0.2f);

//    entity4->assign<ComplexTransformation>(Vector<3> {2, 0, 0}, Vector<3> {0, +20, 0});
//    entity4->assign<ColorMap>(statureTexture);
//    entity4->assign<RawModel>(model);
//    entity4->assign<LightReflection>(1.f, 0.2f);

    entity2->assign<LightSource>(Vector<3>(243.0 / 255.0, 229.0 / 255.0, 188.0 / 255.0));
    entity2->assign<ComplexTransformation>(Vector<3>(5, 5, 5));
    entity3->assign<ComplexTransformation>(Vector<3> {0, -2, 0}, Vector<3> {0, 0, 0}, Vector<3> {3, 3, 3});
    entity3->assign<ColorMap>(texture);
    entity3->assign<RawModel>(groundModel);
    entity3->assign<LightReflection>(1.f, 0.2f);

    master.mainloop();
    return 0;
}