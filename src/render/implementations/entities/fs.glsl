#version 330 core
#extension GL_ARB_explicit_uniform_location : require

in vec4 worldPosition;
in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector[4];

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

    vec3 unitNormal = normalize(surfaceNormal);

    // dont do any diffuse lighting if there are no lights at all
    vec3 totalDiffuse   = vec3(lightCount == 0 ? 1:0);
    vec3 totalSpecular  = vec3(0);

    for(int i = 0; i < lightCount; i++){
        float dist       = length(toLightVector[i]);
        vec3  unitLight  = toLightVector[i] / dist;
        float scalar     = lights[i].factors.x * pow(lights[i].factors.y, lights[i].factors.z / dist);
        float angleScale = dot(unitLight, surfaceNormal);

        float brightness = max(angleScale,0.2);

        totalDiffuse = totalDiffuse + (brightness * lights[i].color) / scalar;
    }

    color = vec4(totalDiffuse,1.0) * textureColour + vec4(totalSpecular,0.0);
}