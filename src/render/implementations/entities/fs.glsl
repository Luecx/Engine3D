#version 330 core
#extension GL_ARB_explicit_uniform_location : require


in vec2 pass_textureCoords;
in vec3 surfaceNormal;

out vec4 color;

uniform sampler2D colormap;
void main()
{
    vec4 textureColour = texture(colormap,pass_textureCoords);

    vec3 h = surfaceNormal;

    color = textureColour;
}