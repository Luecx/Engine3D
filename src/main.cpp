

#define GLFW_INCLUDE_NONE
#include "camera/PerspectiveCamera.h"
#include "component/GroupableGameObject.h"
#include "glad.h"
#include "loader/OBJLoader.h"
#include "loader/TextureLoader.h"
#include "loader/VAOLoader.h"
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

    PerspectiveCamera camera {};
    camera.getPosition()[2] = 5;
    camera.getRotation()[1] = 0;
    camera.getProjectionMatrix();
    float positions[] = {
        -0.5f, -0.5f, -0.5,    // 0
        0.5f,  -0.5f, -0.5,    // 1
        0.5f,  0.5f,  -0.5,    // 2
        -0.5f, 0.5f,  -0.5,    // 3
    };
    unsigned int       indices[] = {0, 1, 2, 2, 3, 0};

    std::vector<float> pos_vec {};
    std::vector<int>   indices_vec {};
    for (int i = 0; i < 12; i++)
        pos_vec.push_back(positions[i]);
    for (int i = 0; i < 6; i++)
        indices_vec.push_back(indices[i]);

    //    RawModel model = loadToVao(pos_vec, indices_vec);

    RawModel     model   = loadOBJ("F:\\OneDrive\\ProgrammSpeicher\\IntelliJ\\3DGameEngine\\res\\models\\cube.obj", false);
    Texture      texture = loadTexture("C:\\Users\\Luecx\\CLionProjects\\Engine3D\\res\\colormaps\\xoK5F.bmp");
    Texture      texture1 = texture;
    std::cout << texture.getTextureId() << std::endl;

    EntitySystem system {};
    system.enable();
    system.model = model;

    glBindVertexArray(model.vaoID);
    glEnableVertexAttribArray(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        system.render(camera);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        //        camera.getRotation()[1] += 0.01;
        //        std::cout << camera.getRotation() << std::endl;
        //        std::cout << camera.getPosition() << std::endl;
        //        std::cout << camera.getViewMatrix() << std::endl;
        //        std::cout << camera.getTransformationMatrix() << std::endl;
    }

    glfwTerminate();
    return 0;
}