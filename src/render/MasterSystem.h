//
// Created by Luecx on 06.06.2021.
//

#ifndef ENGINE3D_SRC_RENDER_MASTERSYSTEM_H_
#define ENGINE3D_SRC_RENDER_MASTERSYSTEM_H_

#include "../components/LightSource.h"
#include "../control/ControlSystem.h"
#include "../core/glerror.h"
#include "../ecs/ecs.h"
#include "../glad.h"
#include "../resources/ResourceManager.h"
#include "entities/EntitySystem.h"
#include "normals/NormalSystem.h"
#include "shadow/ShadowSystem.h"

#include <GLFW/glfw3.h>
#include <vector>
class MasterSystem {

    public:
    ecs::ECS     ecs {};
    ecs::Entity* system;
    GLFWwindow*  window;

    // list of systems which can be used
    ShadowSystem shadowSystem;
    EntitySystem entitySystem;
    NormalSystem normalSystem;

    // resource manager
    ResourceManager resourceManager;

    // list of basic systems which work in the background
    ControlSystem controlSystem;

    private:
    bool init() {

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
        //        glfwSwapInterval( 0 );

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize OpenGL context" << std::endl;
            return false;
        }

        std::cout << glGetString(GL_VERSION) << std::endl;
        return true;
    }

    public:
    MasterSystem() {
        init();
        system = ecs.spawn();
        system->assign<MasterSystem*>(this);
        system->assign<GLFWwindow*>(window);

        shadowSystem = {};
        shadowSystem.enable();
        ecs.addSystem(&shadowSystem);

        entitySystem = {};
        entitySystem.enable();
        ecs.addSystem(&entitySystem);

        normalSystem = {};
        normalSystem.enable();
        ecs.addSystem(&normalSystem);

        controlSystem = {};
        ecs.addSystem(&controlSystem);
    }

    void mainloop() {
        double previousTime = glfwGetTime();
        while (!glfwWindowShouldClose(window)) {
            double currentTime = glfwGetTime();
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            ecs.process(currentTime - previousTime);
            GL_ERROR_CHECK();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
            GL_ERROR_CHECK();

            /* Poll for and process events */
            glfwPollEvents();
            GL_ERROR_CHECK();
            previousTime = currentTime;
        }

        GL_ERROR_CHECK();
        ecs.destroy();
        GL_ERROR_CHECK();

        resourceManager.remove_all();

        glfwTerminate();
    }
};

#endif    // ENGINE3D_SRC_RENDER_MASTERSYSTEM_H_
