#version 330 core
#extension GL_ARB_explicit_uniform_location : require

in vec4 worldPosition;
in vec2 pass_textureCoords;
in vec3 surfaceNormal;

out vec4 color;

struct LightSource
{
    vec3 position;
    vec3 color;
    vec3 factors;
};

uniform sampler2D colormap;
uniform LightSource lights[4];
uniform int lightCount;
void main()
{
    vec4 textureColour = texture(colormap,pass_textureCoords);

    vec3 h = surfaceNormal;

    vec3 lightColor = vec3(0,0,0);
    for(int i = 0; i < lightCount; i++){
        float dist = distance(worldPosition.xyz, lights[i].position);
        float scalar = lights[i].factors.x * pow(lights[i].factors.y, lights[i].factors.z * dist);
        lightColor  += lights[i].color * clamp(scalar,0.1,1);
    }

    color = textureColour + vec4(lightColor,1);
}