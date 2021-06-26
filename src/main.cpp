
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
#include "components/ShadowCaster.h"




struct Ball{
    Vector<3> velocity{};
};

struct CollisionEvent{

    ecs::Entity* entity;

};

struct CustomSystem : public ecs::System{
    double time = 0;
    void process(ecs::ECS* ecs, double delta) override {
        time += delta;

        ecs::Entity* light = ecs->first<LightSource, ComplexTransformation>();
        Vector<3>& lightPos = light->get<ComplexTransformation>()->getPosition();
        lightPos[0] = 20 * cos(time);
        lightPos[2] = 20 * sin(time);


        std::cout <<"\r"<< 1.0 / delta << " fps" << std::flush;

        ecs::Entity* entity = ecs->first<Ball,ComplexTransformation>();

        Vector<3>& velocity = entity->get<Ball>()->velocity;
        Vector<3>& position = entity->get<ComplexTransformation>()->getPosition();

        velocity[1] += -9.81 * delta;
        position[1] += velocity[1] * delta;
        if(position[1] <= 0){
            position[1] = 0;
            velocity[1] = -velocity[1] * 0.8;
        }
    }
};

struct CollisionListener : public ecs::EventListener<CollisionEvent>{

};

int main() {

    MasterSystem      master {};


    PerspectiveCamera camera {};
    camera.setPosition({0,3,3});
    camera.setRotation({-4,0,0});
    ecs::Entity* cameraEntity = master.ecs.spawn();
    cameraEntity->assign<Camera*>(&camera);
    cameraEntity->assign<SimpleControl>(2.0f,2.0f);

    RawModel       modelIco       = loadOBJ(R"(C:\Users\Luecx\CLionProjects\Engine3D\res\models\sphere.obj)");
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

    // ball
    entity->assign<ComplexTransformation>(Vector<3> {0,10,0}, Vector<3> {0, 0, 0}, Vector<3> {1,1,1});
    entity->assign<RawModel>(modelIco);
    entity->assign<ColorMap>(texture);
    entity->assign<LightReflection>(32.f);
    entity->assign<Ball>();

    // light source
    entity2->assign<ColorMap>(texture);
    entity2->assign<RawModel>(modelIco);
    entity2->assign<LightReflection>(1.f);
    entity2->assign<LightSource>(Vector<3>(243.0 / 255.0, 229.0 / 255.0, 188.0 / 255.0), Vector<3>{1,0.5,0.01});
    entity2->assign<ShadowCaster>(20.0,0.1,50.0);
    entity2->assign<ComplexTransformation>(Vector<3>(20,20,20),Vector<3>(0,0,0),Vector<3>(0.1,0.1,0.1));

    // floor
    entity3->assign<ComplexTransformation>(Vector<3> {0, -1, 0}, Vector<3> {0, 0, 0}, Vector<3> {10,10,10});
    entity3->assign<ColorMap>(texture);
    entity3->assign<RawModel>(groundModel);
    entity3->assign<LightReflection>(32.f);

    master.mainloop();
    return 0;
}