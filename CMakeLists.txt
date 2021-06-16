cmake_minimum_required(VERSION 3.19)
project(Engine3D)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)


set(CMAKE_CXX_STANDARD 17)


add_executable(Engine3D
        src/glad.h
        src/glad.c
        src/main.cpp
        src/math/Matrix.cpp
        src/math/Matrix.h
        src/math/Vector.cpp
        src/math/Vector.h
        src/math/Precision.h
        src/transformation/ComplexGameObject.cpp
        src/transformation/ComplexGameObject.h
        src/transformation/GroupableGameObject.cpp
        src/transformation/GroupableGameObject.h
        src/model/RawModel.cpp
        src/model/RawModel.h
        src/loader/Loader.cpp
        src/loader/Loader.h
        src/material/Texture.cpp
        src/material/Texture.h
        src/loader/TextureLoader.h
        src/loader/TextureLoader.cpp
        src/loader/VAOLoader.h
        src/loader/VAOLoader.cpp
        src/render/ShaderProgram.cpp
        src/render/ShaderProgram.h
        src/render/RenderSystem.cpp
        src/render/RenderSystem.h
        src/loader/OBJLoader.cpp
        src/loader/OBJLoader.h
        src/camera/Camera.cpp
        src/camera/Camera.h
        src/camera/PerspectiveCamera.cpp
        src/camera/PerspectiveCamera.h
        src/render/implementations/entities/EntityShader.h
        src/render/implementations/entities/EntitySystem.h
        src/material/EntityMaterial.cpp
        src/material/EntityMaterial.h
        src/entities/TexturedModel.cpp
        src/entities/TexturedModel.h
        src/entities/Entity.cpp
        src/entities/Entity.h
        src/transformation/Group.cpp
        src/transformation/Group.h
        src/camera/OrthogonalCamera.cpp
        src/camera/OrthogonalCamera.h src/light/LightSource.cpp src/light/LightSource.h src/render/MasterSystem.cpp src/render/MasterSystem.h
        src/ecs/core.h
        src/ecs/assign.h
        src/ecs/component.h
        src/ecs/core.h
        src/ecs/entity.h
        src/ecs/event.h
        src/ecs/hash.h
        src/ecs/iterator.h
        src/ecs/system.h
        src/ecs/types.h)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDOUBLE_PRECISION")

target_link_libraries(Engine3D glfw)
target_link_libraries(Engine3D OpenGL::GL)
target_link_libraries(Engine3D -static-libgcc -static-libstdc++)


set(CMAKE_EXE_LINKER_FLAGS " -static")
