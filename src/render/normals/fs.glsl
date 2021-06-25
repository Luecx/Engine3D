#version 330 core
#extension GL_ARB_explicit_uniform_location : require

in vec4 vertex_color;
out vec4 Out_Color;
void main()
{
    Out_Color = vertex_color;
}