#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// from vs
in VS_OUT{
    vec3 fragPos;
    vec2 texCoords;
    vec3 tangentCameraPos;
    vec3 tangentFragPos;
    vec3 tangentLightPos[4];
} fsIn;

// to pixel
out vec4 color;

// material
uniform float shineDamper;
uniform float reflectivity;

// texture stretching
uniform float textureStretch;

// maps
uniform sampler2D colorMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;

uniform bool useNormalMap;
uniform bool useSpecularMap;

// lights
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
    vec4 textureColour = texture(colorMap,fsIn.texCoords * textureStretch);

    vec3 lightColor = vec3(0,0,0);
    vec3 unitNormal = vec3(0,0,1);

    // adjust the normal using the TBN matrix if normal mapping is supported
    if(useNormalMap){
        unitNormal = texture(normalMap, fsIn.texCoords * textureStretch).rgb;
        unitNormal = unitNormal * 2.0 - 1.0;
        unitNormal = normalize(unitNormal);
    }

    // dont do any diffuse lighting if there are no lights at all
    vec3 totalDiffuse   = vec3(lightCount == 0 ? 1:0);
    vec3 totalSpecular  = vec3(0,0,0);

    vec3 unitVectorToCamera = normalize(fsIn.tangentCameraPos);

    for(int i = 0; i < lightCount; i++){
        float dist       = length(fsIn.tangentLightPos[i]);
        vec3  unitLight  = normalize(fsIn.tangentLightPos[i]);
        float scalar     = lights[i].factors.x * pow(lights[i].factors.y, lights[i].factors.z * dist);
        float angleScale = dot(unitLight, unitNormal);

        float brightness     = max(angleScale,0.2);
        vec3  lightDirection = -unitLight;
        vec3  reflectedLight = reflect(lightDirection, unitNormal);

        float specularFactor = max(0.0,dot(reflectedLight, normalize(fsIn.tangentCameraPos)));
        float dampedFactor   = pow(specularFactor,shineDamper);


        totalDiffuse  = totalDiffuse  + (brightness * lights[i].color) * scalar;
        if(angleScale > 0)
            totalSpecular = totalSpecular + (dampedFactor * reflectivity * lights[i].color) * scalar;
    }

    color = vec4(totalDiffuse,1.0) * textureColour + vec4(totalSpecular,1.0);
}