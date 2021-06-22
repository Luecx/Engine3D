//
// Created by Luecx on 06.06.2021.
//

#ifndef ENGINE3D_SRC_RENDER_MASTERSYSTEM_H_
#define ENGINE3D_SRC_RENDER_MASTERSYSTEM_H_

#include "../components/LightSource.h"
#include "../ecs/ecs.h"
#include "../glad.h"
#include "implementations/entities/EntitySystem.h"

#include <GLFW/glfw3.h>
#include <vector>
class MasterSystem {

    public:
    ecs::ECS     ecs {};
    ecs::Entity* system;
    GLFWwindow*  window;

    // list of systems which can be used
    EntitySystem entitySystem;

    private:
    bool         init() {

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

    public:
    MasterSystem() {
        init();
        system = ecs.spawn();
        system->assign<MasterSystem*>(this);
        system->assign<GLFWwindow  *>(window);

        entitySystem = {};
        entitySystem.enable();
        ecs.addSystem(&entitySystem);

    }

    void mainloop() {
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            //        system.render(camera, &ecs);


            ecs.process(0.0);
//            std::cout << "swapping "<< std::endl;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);


            /* Poll for and process events */
            glfwPollEvents();
        }
        glfwTerminate();
    }
};

#endif    // ENGINE3D_SRC_RENDER_MASTERSYSTEM_H_
