

#define GLFW_INCLUDE_NONE
#include "camera/OrthogonalCamera.h"
#include "camera/PerspectiveCamera.h"
#include "components/LightSource.h"
#include "ecs/core.h"
#include "loader/OBJLoader.h"
#include "loader/TextureLoader.h"
#include "loader/VAOLoader.h"
#include "material/ColorMap.h"
#include "material/EntityMaterial.h"
#include "math/Matrix.h"
#include "math/Vector.h"
#include "render/MasterSystem.h"
#include "render/ShaderProgram.h"
#include "render/implementations/entities/EntityShader.h"
#include "render/implementations/entities/EntitySystem.h"
#include "transformation/ComplexTransformation.h"

int main(void) {

    MasterSystem master{};


    PerspectiveCamera camera {};
//    camera.setLeft(-6);
//    camera.setRight(6);
//    camera.setTop(4);
//    camera.setBottom(-4);

    camera.getPosition()[2] = 3;
    camera.getRotation()[1] = 0;
    camera.getProjectionMatrix();


    ecs::Entity* cameraEntity = master.ecs.spawn();
    cameraEntity->assign<Camera*>(&camera);


    RawModel     model   = loadOBJ(R"(F:\OneDrive\ProgrammSpeicher\IntelliJ\3DGameEngine\res\models\icosphere.obj)", false);
    Texture      texture = loadTexture(R"(C:\Users\Luecx\CLionProjects\Engine3D\res\colormaps\xoK5F.bmp)");
    EntityMaterial material{texture};

    ecs::Entity* entity = master.ecs.spawn();
    ecs::Entity* entity2 = master.ecs.spawn();
    entity->assign<ComplexTransformation>();
    entity->assign<ColorMap>(texture);
    entity->assign<RawModel>(model);
    entity2->assign<LightSource>(Vector<3>(1,1,1));
    entity2->assign<ComplexTransformation>(Vector<3>(10,10,10));


    master.mainloop();
    return 0;
}