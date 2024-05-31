#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoords;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;

out VS_OUT {
    vec3 fragPos;
    vec3 fragNormal;
    vec3 fragTangent;
    vec3 fragBitangent;
    vec4 fragPosLightSpace;
    vec2 texCoords;
} vsOut;

struct LightSource {
    vec3 position;
    vec3 color;
    vec3 factors;
};

uniform vec3 cameraPosition;
uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 shadowViewMatrix;
uniform bool useNormalMap;

uniform LightSource lights[4];
uniform int lightCount;

void main()
{
    vec4 worldPosition = transformationMatrix * vec4(position, 1.0);
    vec3 N = normalize(mat3(transformationMatrix) * normal); // Correct normal transformation
    vec3 T = normalize(mat3(transformationMatrix) * tangent); // Correct tangent transformation
    T = normalize(T - dot(T, N) * N); // Re-orthogonalize T with respect to N
    vec3 B = cross(N, T); // Retrieve perpendicular vector B with the cross product of T and N

    vsOut.fragPos = worldPosition.xyz;
    vsOut.fragNormal = N;
    vsOut.fragTangent = T;
    vsOut.fragBitangent = B;
    vsOut.texCoords = textureCoords;
    vsOut.fragPosLightSpace = shadowViewMatrix * worldPosition;

    gl_Position = projectionMatrix * viewMatrix * worldPosition;
}
