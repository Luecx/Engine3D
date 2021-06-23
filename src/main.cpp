
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




struct CustomSystem : public ecs::System{
    void process(ecs::ECS* ecs, double delta) override {
        ecs::Entity* entity = ecs->first<LightSource>();
//        entity->get<ComplexTransformation>()->getPosition()[0] -= delta;
//        entity->get<ComplexTransformation>()->getPosition()[2] -= delta;
    }
};


int main() {

    MasterSystem      master {};

    PerspectiveCamera camera {};

    camera.getPosition()[2] = 1;
    camera.getPosition()[1] = 1;

    camera.getProjectionMatrix();

    ecs::Entity* cameraEntity = master.ecs.spawn();
    cameraEntity->assign<Camera*>(&camera);
    cameraEntity->assign<SimpleControl>();

    RawModel       modelIco       = loadOBJ(R"(C:\Users\Luecx\CLionProjects\Engine3D\res\models\cube.obj)");
    RawModel       groundModel    = loadOBJ(R"(C:\Users\Luecx\CLionProjects\Engine3D\res\models\groundSmall.obj)");
    RawModel       model          = loadOBJ(R"(C:\Users\Luecx\CLionProjects\Engine3D\res\models\lucy.obj)");
    Texture        texture        = loadTexture(R"(C:\Users\Luecx\CLionProjects\Engine3D\res\colormaps\uv.bmp)");
    Texture        statureTexture = loadTexture(R"(C:\Users\Luecx\CLionProjects\Engine3D\res\colormaps\white.bmp)");
    Texture        normalTexture  = loadTexture(R"(C:\Users\Luecx\CLionProjects\Engine3D\res\normals\rustyMetal.bmp)");

    Texture        cBrick         = loadTexture(R"(C:\Users\Luecx\CLionProjects\Engine3D\res\colormaps\bricks.bmp)");
    Texture        nBrick         = loadTexture(R"(C:\Users\Luecx\CLionProjects\Engine3D\res\normals\bricks.bmp)");
    Texture        dBrick         = loadTexture(R"(C:\Users\Luecx\CLionProjects\Engine3D\res\heightmaps\bricks.bmp)");

    ecs::Entity*   entity  = master.ecs.spawn();
    ecs::Entity*   entity2 = master.ecs.spawn();
    ecs::Entity*   entity3 = master.ecs.spawn();

    CustomSystem custom_system{};
    master.ecs.addSystem(&custom_system);

    entity->assign<ComplexTransformation>(Vector<3> {0,0.1,0}, Vector<3> {0, 0, 0}, Vector<3> {1,1,1});
    entity->assign<RawModel>(groundModel);
    entity->assign<ColorMap>(cBrick);
    entity->assign<NormalMap>(nBrick);
    entity->assign<ParallaxMap>(dBrick, 0.01f);
//    entity->assign<TextureStretch>(1ff);
    entity->assign<LightReflection>(1.f, 0.2f);
//    entity->assign<DisplayNormal>();


    entity2->assign<ColorMap>(statureTexture);
    entity2->assign<RawModel>(modelIco);
    entity2->assign<LightReflection>(1.f, 0.2f);
    entity2->assign<LightSource>(Vector<3>(243.0 / 255.0, 229.0 / 255.0, 188.0 / 255.0), Vector<3>{1,0.5,0.01});
    entity2->assign<ComplexTransformation>(Vector<3>(3, 5, 3),Vector<3>(0,0,0),Vector<3>(0.1,0.1,0.1));

    entity3->assign<ComplexTransformation>(Vector<3> {0, 0, 0}, Vector<3> {0, 0, 0}, Vector<3> {2,2,2});
    entity3->assign<ColorMap>(texture);
    entity3->assign<RawModel>(groundModel);
    entity3->assign<LightReflection>(1.f, 0.2f);
    entity3->assign<DisplayNormal>();

    master.mainloop();
    return 0;
}