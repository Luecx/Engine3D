

#define GLFW_INCLUDE_NONE
#include "camera/OrthogonalCamera.h"
#include "camera/PerspectiveCamera.h"
#include "transformation/Group.h"
#include "transformation/GroupableGameObject.h"
#include "entities/Entity.h"
#include "entities/TexturedModel.h"
#include "glad.h"
#include "loader/OBJLoader.h"
#include "loader/TextureLoader.h"
#include "loader/VAOLoader.h"
#include "material/EntityMaterial.h"
#include "math/Matrix.h"
#include "math/Vector.h"
#include "render/ShaderProgram.h"
#include "render/implementations/entities/EntityShader.h"
#include "render/implementations/entities/EntitySystem.h"

#include <GLFW/glfw3.h>
#include <cstdarg>
#include <iostream>
#include <unistd.h>

GLFWwindow* window;

bool        init() {

    /* Initialize the library */
    if (!glfwInit())
        return false;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return false;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    return true;
}

int main(void) {

    if (!init()) {
        return -1;
    }

    OrthogonalCamera camera {};
    camera.setLeft(-6);
    camera.setRight(6);
    camera.setTop(4);
    camera.setBottom(-4);

    camera.getPosition()[2] = 3;
    camera.getRotation()[1] = 0;
    camera.getProjectionMatrix();

    //    RawModel model = loadToVao(pos_vec, indices_vec);

    RawModel     model   = loadOBJ(R"(F:\OneDrive\ProgrammSpeicher\IntelliJ\3DGameEngine\res\models\cube.obj)", false);
    Texture      texture = loadTexture(R"(C:\Users\Luecx\CLionProjects\Engine3D\res\colormaps\xoK5F.bmp)");
    EntityMaterial material{texture};
    TexturedModel texturedModel{model, material};


    EntitySystem system {};
    system.enable();

    Group group{};


    std::vector<Entity*> entities{};
    for(int i = 1; i < 2; i++){
        for(int n = 1; n < 2;n++)
            for(int j = 1; j < 2;j++){
            Entity* entity = new Entity();
            entity->getPosition()[0] = i * 4 - 4;
            entity->getPosition()[1] = n * 4 - 4;
            entity->getPosition()[2] = j * 4 - 4;
            entity->texturedModel = texturedModel;
            entities.push_back(entity);
            system.addElement(entity);

            group.addChild(entity);
        }
    }


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        system.render(camera);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        group.getRotation()[1] += 1;
        group.getRotation()[2] -= 0.6;
        group.getRotation()[0] += 1.2;

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}