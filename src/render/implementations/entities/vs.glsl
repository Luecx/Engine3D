#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoords;
layout(location = 2) in vec3 normal;


out vec2 pass_textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector[4];

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


struct LightSource
{
    vec3 position;
    vec3 color;
    vec3 factors;
};

uniform LightSource lights[4];
uniform int lightCount;

void main()
{

    vec4 worldPosition = transformationMatrix * vec4(position,1.0);

    gl_Position         = projectionMatrix * viewMatrix * worldPosition;
    pass_textureCoords  = textureCoords;
    surfaceNormal       = (transformationMatrix * vec4(normal, 0.0)).xyz;

    for(int i=0;i<lightCount;i++){
        toLightVector[i] = lights[i].position - worldPosition.xyz;
    }

}