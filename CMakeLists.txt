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
        src/resources/RawModel.cpp
        src/resources/RawModel.h
        src/loader/Loader.cpp
        src/loader/Loader.h
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
        src/render/entities/EntityShader.h
        src/render/entities/EntitySystem.h
        src/render/normals/NormalShader.h
        src/render/normals/NormalSystem.h
        src/resources/Texture.cpp
        src/resources/Texture.h
        src/material/MaterialMap.h
        src/material/MaterialMap.cpp
        src/camera/OrthogonalCamera.cpp
        src/camera/OrthogonalCamera.h
        src/render/MasterSystem.cpp
        src/render/MasterSystem.h
        src/ecs/core.h
        src/ecs/assign.h
        src/ecs/component.h
        src/ecs/core.h
        src/ecs/entity.h
        src/ecs/event.h
        src/ecs/hash.h
        src/ecs/iterator.h
        src/ecs/system.h
        src/ecs/types.h
        src/components/LightSource.h
        src/components/LightSource.cpp
        src/transformation/Transformation.h
        src/transformation/Transformation.cpp
        src/transformation/ComplexTransformation.h
        src/transformation/ComplexTransformation.cpp
        src/material/LightReflection.h
        src/material/TextureStretch.h
        src/control/ControlSystem.h
        src/control/ControlSystem.cpp
        src/math/angle.h
        src/math/Projection.h
        src/math/Projection.cpp
        src/math/angle.cpp
        src/core/config.h
        src/render/entities/EntitySystem.cpp
        src/render/entities/EntityShader.cpp
        src/render/shadow/ShadowShader.cpp
        src/render/shadow/ShadowShader.h
        src/render/shadow/ShadowSystem.cpp
        src/render/shadow/ShadowSystem.h
        src/buffer/FrameBufferObject.cpp
        src/buffer/FrameBufferObject.h
        src/components/ShadowCaster.cpp src/components/ShadowCaster.h
        src/gldata/GLData.cpp
        src/gldata/GLData.h
        src/gldata/TextureID.cpp
        src/gldata/TextureID.h
        src/gldata/VAOId.cpp
        src/gldata/VAOId.h
        src/gldata/VBOId.cpp
        src/gldata/VBOId.h
        src/core/glerror.h
        src/resources/ResourceManager.cpp
        src/resources/ResourceManager.h
        src/resources/Resource.cpp
        src/resources/Resource.h
)


# ignore and hide all warnings


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDOUBLE_PRECISION")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W")

target_link_libraries(Engine3D glfw OpenGL::GL)

# debugging symbols
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# set(CMAKE_EXE_LINKER_FLAGS " -static")
