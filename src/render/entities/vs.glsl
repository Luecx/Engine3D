#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoords;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;


out VS_OUT{
    vec3 fragPos;
    vec2 texCoords;
    vec3 tangentCameraPos;
    vec3 tangentFragPos;
    vec3 tangentLightPos[4];
} vsOut;


struct LightSource{
    vec3 position;
    vec3 color;
    vec3 factors;
};

uniform vec3 cameraPosition;
uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform bool useNormalMap;

uniform LightSource lights[4];
uniform int lightCount;

void main()
{

    vec4 worldPosition          = transformationMatrix * vec4(position, 1.0);
    mat4 modelViewMatrix        = viewMatrix * transformationMatrix;

    gl_Position         = projectionMatrix * viewMatrix * worldPosition;

    vec3 T = normalize((transformationMatrix * vec4(tangent, 0.0)).xyz);
    vec3 N = normalize((transformationMatrix * vec4(normal, 0.0)).xyz);
    // re-orthogonalize T with respect to N
    T = normalize(T - dot(T, N) * N);
    // then retrieve perpendicular vector B with the cross product of T and N
    vec3 B = cross(N, T);

    mat3 TBN = transpose(mat3(T, B, N));

    for (int i=0;i<lightCount;i++){
        vsOut.tangentLightPos[i] = TBN * (lights[i].position - worldPosition.xyz);
    }

    vsOut.tangentCameraPos = TBN * ( cameraPosition.xyz - worldPosition.xyz);
    vsOut.tangentFragPos   = TBN * ( worldPosition.xyz);
    vsOut.fragPos          =       ( worldPosition.xyz);
    vsOut.texCoords        =       ( textureCoords);
}