#version 330 core
in vec4 position;
out vec2 pos;
uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
//    gl_Position = projectionMatrix * viewMatrix * transformationMatrix * position;
    gl_Position = projectionMatrix * viewMatrix * position;
    pos.x = gl_Position.x / gl_Position.w;
    pos.y = gl_Position.y / gl_Position.w;
//    gl_Position.z = -0.9;
//    gl_Position.w = 0.3;
}