#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoords;
layout(location = 2) in vec3 normal;

out vec2 pass_textureCoords;
out vec3 surfaceNormal;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
//    gl_Position = projectionMatrix * viewMatrix * transformationMatrix * position;
    gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(position,1.0);
    pass_textureCoords = textureCoords;
    surfaceNormal = (transformationMatrix * vec4(normal,0.0)).xyz;
//    gl_Position.z = -0.9;
//    gl_Position.w = 0.3;
}