//
// Created by Luecx on 23.06.2021.
//

#include "ControlSystem.h"

#include "../camera/Camera.h"

#include <GLFW/glfw3.h>

void simpleControl(Camera* camera, SimpleControl &control, GLFWwindow* window, double delta) {
    Vector<3> forward = camera->getZAxis();
    forward.normalise();
    forward *= -1;

    Vector<3> up      = camera->getYAxis();
    up.normalise();

    Vector<3> right      = camera->getXAxis();
    right.normalise();

    if(glfwGetKey(window, GLFW_KEY_W)){
        camera->getPosition() += forward * delta * control.forwardSpeed;
    }
    if(glfwGetKey(window, GLFW_KEY_S)){
        camera->getPosition() -= forward * delta * control.forwardSpeed;
    }
    if(glfwGetKey(window, GLFW_KEY_A)){
        camera->getPosition() -= right * delta * control.sideSpeed;
    }
    if(glfwGetKey(window, GLFW_KEY_D)){
        camera->getPosition() += right * delta * control.sideSpeed;
    }

    if(glfwGetKey(window, GLFW_KEY_UP)){
        camera->rotate(right, delta * control.rotationSpeed);
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN)){
        camera->rotate(right, -delta * control.rotationSpeed);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT)){
        camera->rotate(up, delta * control.rotationSpeed);
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT)){
        camera->rotate(up,-delta * control.rotationSpeed);
    }
    if(glfwGetKey(window, GLFW_KEY_E)){
        camera->rotate(forward, delta * control.rotationSpeed);
    }
    if(glfwGetKey(window, GLFW_KEY_Q)){
        camera->rotate(forward,-delta * control.rotationSpeed);
    }
}

void ControlSystem::process(ecs::ECS* ecs, double delta) {

    GLFWwindow* window = ecs->first<GLFWwindow*>()->get<GLFWwindow*>().component;

    // process simple controls
    for(ecs::Entity* e:ecs->each<Camera*, SimpleControl>()){
        simpleControl(e->get<Camera*>().get(), e->get<SimpleControl>().get(), window, delta);
    }


}

