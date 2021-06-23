#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoords;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;


out Vertex
{
    vec4 position;
    vec4 normal;
    vec4 tangent;
    vec4 color;
} vertex;

void main()
{


    vertex.position= vec4(position, 1.0);
    vertex.normal  = vec4(normal,1.0);
    vertex.tangent = vec4(tangent,1.0);
    vertex.color   =  vec4(1.0, 1.0, 0.0, 1.0);


}