#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoords;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;


out vec2 pass_textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector[4];
out vec3 toCameraVector;
out mat3 TBN;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform bool useNormalMap;

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

    vec4 worldPosition          = transformationMatrix * vec4(position, 1.0);
    mat4 modelViewMatrix        = viewMatrix * transformationMatrix;
    vec4 positionRelativeToCam  = modelViewMatrix * vec4(position, 1.0);

    gl_Position         = projectionMatrix * positionRelativeToCam;
    pass_textureCoords  = textureCoords;

    surfaceNormal       = (transformationMatrix * vec4(normal, 0.0)).xyz;

    if(useNormalMap){
        vec3 norm   = normalize(surfaceNormal);
        vec3 tang   = normalize((transformationMatrix * vec4(tangent, 0.0)).xyz);
        vec3 bitang = normalize(cross(norm, tang));

        TBN = transpose(mat3(tang, bitang, norm));
    }

    for(int i=0;i<lightCount;i++){
        toLightVector[i] = lights[i].position - worldPosition.xyz;
    }

    toCameraVector = -positionRelativeToCam.xyz;

}